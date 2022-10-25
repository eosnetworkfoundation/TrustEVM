#include "block_conversion_plugin.hpp"
#include "channels.hpp"
#include "abi_utils.hpp"

#include <fstream>

#include <silkworm/types/transaction.hpp>
#include <silkworm/trie/vector_root.hpp>

struct block_mapping {
   
   static constexpr uint64_t genesis_timestamp = 1648673684000000; //us 
   static constexpr uint64_t block_interval    = 1000000;          //us

   inline static uint32_t timestamp_to_evm_block(uint64_t timestamp) {
      if( timestamp < genesis_timestamp ) {
         SILK_CRIT << "Invalid timestamp: " << timestamp << ", genesis: " << genesis_timestamp;
         assert(timestamp >= genesis_timestamp);
      }
      return 1 + (timestamp - genesis_timestamp)/block_interval;
   }

   inline static uint64_t evm_block_to_timestamp(uint32_t block_num) {
      return genesis_timestamp + block_num * block_interval;
   }

};
using sys = sys_plugin;
class block_conversion_plugin_impl : std::enable_shared_from_this<block_conversion_plugin_impl> {
   public:
      block_conversion_plugin_impl()
        : evm_blocks_channel(appbase::app().get_channel<channels::evm_blocks>()){}

      inline uint32_t endian_reverse_u32( uint32_t x )
      {
         return (((x >> 0x18) & 0xFF)        )
            | (((x >> 0x10) & 0xFF) << 0x08)
            | (((x >> 0x08) & 0xFF) << 0x10)
            | (((x        ) & 0xFF) << 0x18)
            ;
      }

      void load_head() {
         auto head_header = appbase::app().get_plugin<engine_plugin>().get_head_canonical_header();
         if (!head_header) {
            sys::error("Unable to read canonical header");
            return;
         }
         evm_blocks.push_back(silkworm::Block{.header=*head_header});
         
         channels::native_block nb;
         nb.id = eosio::checksum256(head_header->mix_hash.bytes);
         nb.block_num = endian_reverse_u32(*reinterpret_cast<uint32_t*>(head_header->mix_hash.bytes));
         native_blocks.push_back(nb);
      }

      evmc::bytes32 compute_transaction_root(const silkworm::BlockBody& body) {
         if (body.transactions.empty()) {
            return silkworm::kEmptyRoot;
         }

         static constexpr auto kEncoder = [](silkworm::Bytes& to, const silkworm::Transaction& txn) {
            silkworm::rlp::encode(to, txn, /*for_signing=*/false, /*wrap_eip2718_into_string=*/false);
         };

         evmc::bytes32 txn_root{silkworm::trie::root_hash(body.transactions, kEncoder)};

         return txn_root;
      }

      silkworm::Block new_block(uint64_t num, const evmc::bytes32& parent_hash) {
         silkworm::Block new_block;
         new_block.header.parent_hash       = parent_hash;
         new_block.header.difficulty        = 1;
         new_block.header.number            = num;
         new_block.header.gas_limit         = 0x7ffffffffff;
         new_block.header.timestamp         = block_mapping::evm_block_to_timestamp(num)/1e6;
         new_block.header.transactions_root = silkworm::kEmptyRoot;
         //new_block.header.mix_hash
         //new_block.header.nonce           
         //new_block.header.ommers_hash;
         //new_block.header.beneficiary;
         //new_block.header.state_root;
         //new_block.header.receipts_root;
         //new_block.header.logs_bloom;
         //new_block.header.gas_used;
         //new_block.header.extra_data;
         return new_block;
      }

      // Set the mix_hash header field of the `evm_block` to the `native_block` id
      void set_upper_bound(silkworm::Block& evm_block, const channels::native_block& native_block) {
         auto id = native_block.id.extract_as_byte_array();
         static_assert(sizeof(decltype(id)) == sizeof(decltype(evm_block.header.mix_hash.bytes)));
         std::copy(id.begin(), id.end(), evm_block.header.mix_hash.bytes);
      }

      template <typename F>
      void for_each_action(const channels::native_block& block, F&& f) {
         for(const auto& trx: block.transactions) {
            for(const auto& act: trx.actions) {
               f(act);
            }
         }
      }

      inline void init() {
         SILK_DEBUG << "block_conversion_plugin_impl INIT";
         load_head();
         
         native_blocks_subscription = appbase::app().get_channel<channels::native_blocks>().subscribe(
            [this](auto b) {
               
               //SILK_INFO << "--Enter Block #" << b->block_num;

               // Keep the last block before genesis timestamp
               if (b->timestamp <= block_mapping::genesis_timestamp) {
                  SILK_DEBUG << "Before genesis: " << block_mapping::genesis_timestamp <<  " Block #" << b->block_num << " timestamp: " << b->timestamp;
                  native_blocks.clear();
                  native_blocks.push_back(*b);
                  return;
               }
               
               // Add received native block to our local reversible chain.
               // If the received native block can't be linked we remove the forked blocks until the fork point.
               // Also we remove the forked block transactions from the corresponding evm block as they where previously included
               // and update the upper bound block accordingly
               while( !native_blocks.empty() && native_blocks.back().id != b->prev ) {
                  //SILK_DEBUG << "Fork at Block #" << b->block_num;
                  const auto& forked_block = native_blocks.back();

                  while( block_mapping::timestamp_to_evm_block(forked_block.timestamp) < evm_blocks.back().header.number )
                     evm_blocks.pop_back();

                  auto& last_evm_block = evm_blocks.back();
                  for_each_action(forked_block, [&last_evm_block](const auto&){
                     last_evm_block.transactions.pop_back();
                  });

                  native_blocks.pop_back();
                  if( native_blocks.size() && block_mapping::timestamp_to_evm_block(native_blocks.back().timestamp) == last_evm_block.header.number )
                     set_upper_bound(last_evm_block, native_blocks.back());
               }

               if( native_blocks.empty() || native_blocks.back().id != b->prev ) {
                  SILK_CRIT << "Unbale to link block #" << b->block_num;
                  throw std::runtime_error("Unbale to link block");
               }
               native_blocks.push_back(*b);

               // Process the last native block received.
               // We extend the evm chain if necessary up until the block where the received block belongs
               auto evm_num = block_mapping::timestamp_to_evm_block(b->timestamp);
               SILK_INFO << "Expecting evm number: " << evm_num;

               while(evm_blocks.back().header.number < evm_num) {
                  auto& last_evm_block = evm_blocks.back();
                  //if( last_evm_block.header.number != 0 ) {
                     last_evm_block.header.transactions_root = compute_transaction_root(last_evm_block);
                     if (!(last_evm_block.header.number % 1000))
                        SILK_INFO << "Generating EVM #" << last_evm_block.header.number;
                     evm_blocks_channel.publish(80, std::make_shared<silkworm::Block>(last_evm_block));
                  //}
                  evm_blocks.push_back(new_block(last_evm_block.header.number+1, last_evm_block.header.hash()));
               }

               // Add transactions to the evm block
               auto& curr = evm_blocks.back();
               for_each_action(*b, [this, &curr](const auto& act){
                     auto dtx = deserialize_tx(act.data);
                     silkworm::ByteView bv = {(const uint8_t*)dtx.rlpx.data(), dtx.rlpx.size()};
                     silkworm::Transaction evm_tx;
                     if (silkworm::rlp::decode<silkworm::Transaction>(bv, evm_tx) != silkworm::DecodingResult::kOk) {
                        SILK_CRIT << "Failed to decode transaction in block: " << curr.header.number;
                        throw std::runtime_error("Failed to decode transaction");
                     }
                     curr.transactions.emplace_back(std::move(evm_tx));
               });
               //SILK_DEBUG << "Txs added to EVM #" << curr.header.number;
               set_upper_bound(curr, *b);

               // Calculate last irreversible EVM block
               auto lib_timestamp = b->timestamp;
               if(b->lib < native_blocks.back().block_num) {
                  auto it = std::find_if(native_blocks.begin(), native_blocks.end(), [&b](const auto& nb){ return nb.block_num == b->lib; });
                  if(it == native_blocks.end()) {
                     SILK_CRIT << "Unable to find LIB in temp chain (Block #" << b->lib << ")";
                     throw std::runtime_error("Unable to find LIB in temp chain");
                  }
                  lib_timestamp = it->timestamp;
               }

               auto evm_lib = block_mapping::timestamp_to_evm_block(lib_timestamp) - 1;
               //SILK_DEBUG << "EVM LIB: #" << evm_lib;

               // Remove irreversible native blocks
               while(block_mapping::timestamp_to_evm_block(native_blocks.front().timestamp) < evm_lib) {
                  //SILK_DEBUG << "Remove IRR native: #" << native_blocks.front().block_num;
                  native_blocks.pop_front();
               }

               // Remove irreversible evm blocks
               while(evm_blocks.front().header.number < evm_lib) {
                  //SILK_DEBUG << "Remove IRR EVM: #" << evm_blocks.front().header.number;
                  evm_blocks.pop_front();
               }
            }
         );
      }

      inline pushtx deserialize_tx(const std::vector<char>& d) const {
         pushtx tx;
         eosio::convert_from_bin(tx, d);
         return tx;
      }

      void shutdown() {}

      std::list<channels::native_block>             native_blocks;
      std::list<silkworm::Block>                    evm_blocks;
      channels::evm_blocks::channel_type&           evm_blocks_channel;
      channels::native_blocks::channel_type::handle native_blocks_subscription;
};

block_conversion_plugin::block_conversion_plugin() : my(new block_conversion_plugin_impl()) {}
block_conversion_plugin::~block_conversion_plugin() {}

void block_conversion_plugin::set_program_options( appbase::options_description& cli, appbase::options_description& cfg ) {
   cfg.add_options()
      // ("genesis-time", boost::program_options::value<std::string>()->default_value("2022-01-01T00:00:00"),
      //   "Start time for Trust EVM chain")
      // ("evm-abi", boost::program_options::value<std::string>()->default_value("./evm.abi"),
      //   "ABI for TrustEVM runtime")
   ;
}

void block_conversion_plugin::plugin_initialize( const appbase::variables_map& options ) {
   //auto genesis_eos_block  = options.at("genesis-eos-block").as<uint32_t>();
   //auto abi_dir = options.at("evm-abi").as<std::string>();

   my->init();
   SILK_INFO << "Initialized block_conversion Plugin";
}

void block_conversion_plugin::plugin_startup() {
}

void block_conversion_plugin::plugin_shutdown() {
   my->shutdown();
   SILK_INFO << "Shutdown block_conversion plugin";
}
