#include "basic_evm_tester.hpp"
#include <silkworm/execution/address.hpp>

using intx::operator""_u256;

using namespace evm_test;
using eosio::testing::eosio_assert_message_is;
struct exec_output_row {
  uint64_t    id;
  exec_output output;
};
FC_REFLECT(exec_output_row, (id)(output))

struct call_evm_tester : basic_evm_tester {
    /*
      //SPDX-License-Identifier: lgplv3
      pragma solidity ^0.8.0;

      contract Test {
          uint256 public count;
          address public lastcaller;

          function test(uint256 input) public {
              require(input != 0);

              count += input;
              lastcaller = msg.sender;
          }
      }
      */
    // Cost for first time call to test(), extra cost is needed for the lastcaller storage.
    const intx::uint256 gas_fee = suggested_gas_price * 63526;
    // Cost for other calls to test()
    const intx::uint256 gas_fee2 = suggested_gas_price * 29326;
    const std::string contract_bytecode = 
          "608060405234801561001057600080fd5b506102ba806100206000396000f3fe608060405234801561001057600080fd5b50600436106100415760003560e01c806306661abd1461004657806329e99f0714610064578063d097e7a614610080575b600080fd5b61004e61009e565b60405161005b919061014c565b60405180910390f35b61007e60048036038101906100799190610198565b6100a4565b005b61008861010d565b6040516100959190610206565b60405180910390f35b60005481565b600081036100b157600080fd5b806000808282546100c29190610250565b9250508190555033600160006101000a81548173ffffffffffffffffffffffffffffffffffffffff021916908373ffffffffffffffffffffffffffffffffffffffff16021790555050565b600160009054906101000a900473ffffffffffffffffffffffffffffffffffffffff1681565b6000819050919050565b61014681610133565b82525050565b6000602082019050610161600083018461013d565b92915050565b600080fd5b61017581610133565b811461018057600080fd5b50565b6000813590506101928161016c565b92915050565b6000602082840312156101ae576101ad610167565b5b60006101bc84828501610183565b91505092915050565b600073ffffffffffffffffffffffffffffffffffffffff82169050919050565b60006101f0826101c5565b9050919050565b610200816101e5565b82525050565b600060208201905061021b60008301846101f7565b92915050565b7f4e487b7100000000000000000000000000000000000000000000000000000000600052601160045260246000fd5b600061025b82610133565b915061026683610133565b925082820190508082111561027e5761027d610221565b5b9291505056fea2646970667358221220edc009a00fe897643f99e8327c7fb355c96d7b91fb8a7da507513c6b2341acc564736f6c63430008120033";

    call_evm_tester() {
      create_accounts({"alice"_n});
      transfer_token(faucet_account_name, "alice"_n, make_asset(10000'0000));
      create_accounts({"bob"_n});
      transfer_token(faucet_account_name, "bob"_n, make_asset(10000'0000));
      init();
    }

    evmc::address deploy_test_contract(evm_eoa& eoa) {
      // Deploy token contract
      return deploy_contract(eoa, evmc::from_hex(contract_bytecode).value());
    }

    void call_test(const evmc::address& contract_addr, uint64_t amount, name eos, name actor) {

      auto to = evmc::bytes{std::begin(contract_addr.bytes), std::end(contract_addr.bytes)};

      silkworm::Bytes data;
      data += evmc::from_hex("29e99f07").value();   // sha3(test(uint256))[:4]
      data += evmc::bytes32{amount};                // value

      call(eos, to, 0, data, 500000, actor);
    }

    void admincall_test(const evmc::address& contract_addr, uint64_t amount, evm_eoa& eoa, name actor) {
      auto to = evmc::bytes{std::begin(contract_addr.bytes), std::end(contract_addr.bytes)};
      auto from = evmc::bytes{std::begin(eoa.address.bytes), std::end(eoa.address.bytes)};
      silkworm::Bytes data;
      data += evmc::from_hex("29e99f07").value();   // sha3(test(uint256))[:4]
      data += evmc::bytes32{amount};                // value

      admincall(from, to, 0, data, 500000, actor);
    }

    intx::uint256 get_count(const evmc::address& contract_addr, std::optional<exec_callback> callback={}, std::optional<bytes> context={}) {
      exec_input input;
      input.context = context;
      input.to = bytes{std::begin(contract_addr.bytes), std::end(contract_addr.bytes)};

      silkworm::Bytes data;
      data += evmc::from_hex("06661abd").value();   // sha3(count())[:4]
      input.data = bytes{data.begin(), data.end()};

      auto res =  exec(input, callback);

      BOOST_REQUIRE(res);
      BOOST_REQUIRE(res->action_traces.size() == 1);

      // Since callback information was not provided the result of the
      // execution is returned in the action return_value
      auto out = fc::raw::unpack<exec_output>(res->action_traces[0].return_value);
      BOOST_REQUIRE(out.status == 0);
      BOOST_REQUIRE(out.data.size() == 32);

      auto result = intx::be::unsafe::load<intx::uint256>(reinterpret_cast<const uint8_t*>(out.data.data()));
      return result;
    }

    evmc::address get_lastcaller(const evmc::address& contract_addr, std::optional<exec_callback> callback={}, std::optional<bytes> context={}) {
      exec_input input;
      input.context = context;
      input.to = bytes{std::begin(contract_addr.bytes), std::end(contract_addr.bytes)};

      silkworm::Bytes data;
      data += evmc::from_hex("d097e7a6").value();   // sha3(lastcaller())[:4]
      input.data = bytes{data.begin(), data.end()};

      auto res = exec(input, callback);

      BOOST_REQUIRE(res);
      BOOST_REQUIRE(res->action_traces.size() == 1);

      // Since callback information was not provided the result of the
      // execution is returned in the action return_value
      auto out = fc::raw::unpack<exec_output>(res->action_traces[0].return_value);
      BOOST_REQUIRE(out.status == 0);

      BOOST_REQUIRE(out.data.size() >= silkworm::kAddressLength);

      evmc::address result;
      memcpy(result.bytes, out.data.data()+out.data.size() - silkworm::kAddressLength, silkworm::kAddressLength);
      return result;
    }
};

BOOST_AUTO_TEST_SUITE(call_evm_tests)
BOOST_FIXTURE_TEST_CASE(call_test_function, call_evm_tester) try {
  evm_eoa evm1;
  auto total_fund = intx::uint256(vault_balance(evm_account_name));
  // Fund evm1 address with 100 EOS
  transfer_token("alice"_n, evm_account_name, make_asset(1000000), evm1.address_0x());
  auto evm1_balance = evm_balance(evm1);
  BOOST_REQUIRE(!!evm1_balance);
  BOOST_REQUIRE(*evm1_balance == 100_ether);
  total_fund += *evm1_balance;

  // Deploy contract
  auto token_addr = deploy_test_contract(evm1);

  // Deployment gas fee go to evm vault
  BOOST_REQUIRE(*evm_balance(evm1) + intx::uint256(vault_balance(evm_account_name)) == total_fund);

  // Missing authority
  BOOST_REQUIRE_EXCEPTION(call_test(token_addr, 1234, "alice"_n, "bob"_n),
                          missing_auth_exception, eosio::testing::fc_exception_message_starts_with("missing authority"));

  // Account not opened
  BOOST_REQUIRE_EXCEPTION(call_test(token_addr, 1234, "alice"_n, "alice"_n),
                          eosio_assert_message_exception, eosio_assert_message_is("caller account has not been opened"));

  // Open
  open("alice"_n);

  // No sufficient funds in the account so decrementing of balance failed.
  BOOST_REQUIRE_EXCEPTION(call_test(token_addr, 1234, "alice"_n, "alice"_n),
                          eosio_assert_message_exception, eosio_assert_message_is("decrementing more than available"));

  // Transfer enough funds
  transfer_token("alice"_n, evm_account_name, make_asset(1000000), "alice");

  BOOST_REQUIRE(intx::uint256(vault_balance("alice"_n)) == 100_ether);
  auto total_fund2 = intx::uint256(vault_balance("alice"_n)) + intx::uint256(vault_balance(evm_account_name));

  BOOST_REQUIRE_EXCEPTION(call_test(token_addr, 0, "alice"_n, "alice"_n),
                          eosio_assert_message_exception, eosio_assert_message_is("tx executed inline by contract must succeed"));


  // Call and check results 
  call_test(token_addr, 1234, "alice"_n, "alice"_n);
  auto count = get_count(token_addr);
  BOOST_REQUIRE(count == 1234);
  BOOST_REQUIRE(intx::uint256(vault_balance("alice"_n))  == 100_ether - gas_fee);
  // Gas go from alice's vault to evm's vault
  BOOST_REQUIRE(total_fund2 == intx::uint256(vault_balance("alice"_n)) + intx::uint256(vault_balance(evm_account_name)));


  // Advance block so we do not generate same transaction.
  produce_block();

  call_test(token_addr, 4321, "alice"_n, "alice"_n);
  count = get_count(token_addr);
  BOOST_REQUIRE(count == 5555);
  BOOST_REQUIRE(intx::uint256(vault_balance("alice"_n)) == 100_ether - gas_fee - gas_fee2);
  // Gas go from alice's vault to evm's vault
  BOOST_REQUIRE(total_fund2 == intx::uint256(vault_balance("alice"_n)) + intx::uint256(vault_balance(evm_account_name)));

  // Function being called on behalf of reserved address of eos account "alice"
  auto caller = get_lastcaller(token_addr);
  BOOST_REQUIRE(caller == make_reserved_address("alice"_n.to_uint64_t()));

} FC_LOG_AND_RETHROW()

BOOST_FIXTURE_TEST_CASE(admincall_test_function, call_evm_tester) try {
  evm_eoa evm1;
  evm_eoa evm2;

  auto total_fund = intx::uint256(vault_balance(evm_account_name));

  // Fund evm1 address with 100 EOS
  transfer_token("alice"_n, evm_account_name, make_asset(1000000), evm1.address_0x());

  auto evm1_balance = evm_balance(evm1);
  BOOST_REQUIRE(!!evm1_balance);
  BOOST_REQUIRE(*evm1_balance == 100_ether);
  total_fund += *evm1_balance;

  // Deploy contract
  auto token_addr = deploy_test_contract(evm1);

  // Deployment gas fee go to evm vault
  BOOST_REQUIRE(*evm_balance(evm1) + intx::uint256(vault_balance(evm_account_name)) == total_fund);

  // Missing authority
  BOOST_REQUIRE_EXCEPTION(admincall_test(token_addr, 1234, evm2, "alice"_n),
                          missing_auth_exception, eosio::testing::fc_exception_message_starts_with("missing authority"));

  // Account not created
  BOOST_REQUIRE_EXCEPTION( admincall_test(token_addr, 1234, evm2, evm_account_name),
                          eosio_assert_message_exception, eosio_assert_message_is("invalid address"));

  // Transfer small amount to create account
  transfer_token("alice"_n, evm_account_name, make_asset(100), evm2.address_0x());

  auto evm2_balance = evm_balance(evm2);
  BOOST_REQUIRE(!!evm2_balance);
  BOOST_REQUIRE(*evm2_balance == 10_finney);

  // Insufficient funds
  BOOST_REQUIRE_EXCEPTION( admincall_test(token_addr, 1234, evm2, evm_account_name),
                          eosio_assert_message_exception, eosio_assert_message_is("validate_transaction error: 23 Insufficient funds"));

  // Transfer enough funds
  transfer_token("alice"_n, evm_account_name, make_asset(10000), evm2.address_0x());

  BOOST_REQUIRE(evm_balance(evm2) == 1010_finney);
  auto total_fund2 = intx::uint256(vault_balance(evm_account_name)) + *evm_balance(evm2);


  BOOST_REQUIRE_EXCEPTION(admincall_test(token_addr, 0, evm2, evm_account_name),
                          eosio_assert_message_exception, eosio_assert_message_is("tx executed inline by contract must succeed"));


  // Call and check results  
  admincall_test(token_addr, 1234, evm2, evm_account_name);

  auto count = get_count(token_addr);
  BOOST_REQUIRE(count == 1234);
  BOOST_REQUIRE(evm_balance(evm2) == 1010_finney - gas_fee);
  // Gas go from evm2 to evm vault
  BOOST_REQUIRE(total_fund2 == *evm_balance(evm2) + intx::uint256(vault_balance(evm_account_name)));

  // Advance block so we do not generate same transaction.
  produce_block();

  admincall_test(token_addr, 4321, evm2, evm_account_name);
  count = get_count(token_addr);
  BOOST_REQUIRE(count == 5555);
  BOOST_REQUIRE(evm_balance(evm2) == 1010_finney - gas_fee - gas_fee2);
  // Gas go from evm2 to evm vault
  BOOST_REQUIRE(total_fund2 == *evm_balance(evm2) + intx::uint256(vault_balance(evm_account_name)));

  // Function being called on behalf of evm address "evm2"
  auto caller = get_lastcaller(token_addr);
  BOOST_REQUIRE(caller== evm2.address);


} FC_LOG_AND_RETHROW()


BOOST_FIXTURE_TEST_CASE(deploy_contract_function, call_evm_tester) try {
  auto alice_addr = make_reserved_address("alice"_n.to_uint64_t());
  open("alice"_n);
  transfer_token("alice"_n, evm_account_name, make_asset(1000000), "alice");


  auto to = evmc::bytes();

  auto data = evmc::from_hex(contract_bytecode);

  call("alice"_n, to, 0, *data, 1000000, "alice"_n); // nonce 0->1
  
  auto addr = silkworm::create_address(alice_addr, 0); 

  call_test(addr, 1234, "alice"_n, "alice"_n); // nonce 1->2
  auto count = get_count(addr);
  BOOST_REQUIRE(count == 1234);

  // Advance block so we do not generate same transaction.
  produce_block();

  auto from = evmc::bytes{std::begin(alice_addr.bytes), std::end(alice_addr.bytes)};

  admincall(from, to, 0, *data, 1000000, evm_account_name); // nonce 2->3
  
  addr = silkworm::create_address(alice_addr, 2); 
  call_test(addr, 2222, "alice"_n, "alice"_n); // nonce 3->4
  count = get_count(addr);
  BOOST_REQUIRE(count == 2222);
} FC_LOG_AND_RETHROW()



BOOST_AUTO_TEST_SUITE_END()