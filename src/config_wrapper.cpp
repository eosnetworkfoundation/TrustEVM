#pragma once
#include <evm_runtime/config_wrapper.hpp>
#include <evm_runtime/tables.hpp>

namespace evm_runtime {

config_wrapper::config_wrapper(eosio::name self) : _self(self), _config(self, self.value) {
    _exists = _config.exists();
    if(_exists) {
        _cached_config = _config.get();
    }
}

config_wrapper::~config_wrapper() {
    flush();
}

void config_wrapper::flush() {
    if(!is_dirty()) {
        return;
    }
    _config.set(_cached_config, _self);
    clear_dirty();
    _exists = true;
}

bool config_wrapper::exists() {
    return _exists;
}

eosio::unsigned_int config_wrapper::get_version()const { 
    return _cached_config.version;
}

void config_wrapper::set_version(const eosio::unsigned_int version) {
    _cached_config.version = version;
    set_dirty();
}

uint64_t config_wrapper::get_chainid()const {
    return _cached_config.chainid;
}

void config_wrapper::set_chainid(uint64_t chainid) {
    _cached_config.chainid = chainid;
    set_dirty();
}

const eosio::time_point_sec& config_wrapper::get_genesis_time()const {
    return _cached_config.genesis_time;
}

void config_wrapper::set_genesis_time(eosio::time_point_sec genesis_time) {
    _cached_config.genesis_time = genesis_time;
    set_dirty();
}

const eosio::asset& config_wrapper::get_ingress_bridge_fee()const {
    return _cached_config.ingress_bridge_fee;
}

void config_wrapper::set_ingress_bridge_fee(const eosio::asset& ingress_bridge_fee) {
    _cached_config.ingress_bridge_fee = ingress_bridge_fee;
    set_dirty();
}

uint64_t config_wrapper::get_gas_price()const {
    return _cached_config.gas_price;
}

void config_wrapper::set_gas_price(uint64_t gas_price) {
    _cached_config.gas_price = gas_price;
    set_dirty();
}

uint32_t config_wrapper::get_miner_cut()const {
    return _cached_config.miner_cut;
}

void config_wrapper::set_miner_cut(uint32_t miner_cut) {
    _cached_config.miner_cut = miner_cut;
    set_dirty();
}

uint32_t config_wrapper::get_status()const {
    return _cached_config.status;
}

void config_wrapper::set_status(uint32_t status) {
    _cached_config.status = status;
    set_dirty();
}

uint64_t config_wrapper::get_evm_version()const {
    uint64_t current_version = 0;
    if(_cached_config.evm_version.has_value()) {
        current_version = _cached_config.evm_version->get_version(_cached_config.genesis_time, get_current_time());
    }
    return current_version;
}

uint64_t config_wrapper::get_evm_version_and_maybe_promote() {
    uint64_t current_version = 0;
    bool promoted = false;
    if(_cached_config.evm_version.has_value()) {
        std::tie(current_version, promoted) = _cached_config.evm_version->get_version_and_maybe_promote(_cached_config.genesis_time, get_current_time());
    }
    if(promoted) set_dirty();
    return current_version;
}

void config_wrapper::set_evm_version(uint64_t new_version) {
    eosio::check(new_version <= eosevm::max_eos_evm_version, "Unsupported version");
    auto current_version = get_evm_version_and_maybe_promote();
    eosio::check(new_version > current_version, "new version must be greater than the active one");
    _cached_config.evm_version.emplace(evm_version_type{evm_version_type::pending{new_version, get_current_time()}, current_version});
    set_dirty();
}

void config_wrapper::set_fee_parameters(const fee_parameters& fee_params,
                        bool allow_any_to_be_unspecified)
{
    if (fee_params.gas_price.has_value()) {
        _cached_config.gas_price = *fee_params.gas_price;
    } else {
        eosio::check(allow_any_to_be_unspecified, "All required fee parameters not specified: missing gas_price");
    }

    if (fee_params.miner_cut.has_value()) {
        eosio::check(*fee_params.miner_cut <= hundred_percent, "miner_cut cannot exceed 100,000 (100%)");

        _cached_config.miner_cut = *fee_params.miner_cut;
    } else {
        eosio::check(allow_any_to_be_unspecified, "All required fee parameters not specified: missing miner_cut");
    }

    if (fee_params.ingress_bridge_fee.has_value()) {
        eosio::check(fee_params.ingress_bridge_fee->symbol == token_symbol, "unexpected bridge symbol");
        eosio::check(fee_params.ingress_bridge_fee->amount >= 0, "ingress bridge fee cannot be negative");

        _cached_config.ingress_bridge_fee = *fee_params.ingress_bridge_fee;
    }

    set_dirty();
}

void config_wrapper::update_gas_params(double kb_ram_price) {

    // for simplicity, just ensure last (cached) evm_version >= 1, not touching promote logic
    eosio::check(_cached_config.evm_version.has_value() && _cached_config.evm_version->cached_version >= 1,
        "required evm_version at least 1");

    if (!_cached_config.gas_parameter.has_value()) {
        _cached_config.gas_parameter = gas_parameter_type();
    }
    gas_parameter_type &param = *(_cached_config.gas_parameter);

    double gas_per_byte_f = 
        (kb_ram_price * 1e18 / (1024.0)) / (_cached_config.gas_price * (100000 - _cached_config.miner_cut) / 100000);

    // round up to multiple of 8 bytes
    constexpr uint64_t account_bytes = 352;
    constexpr uint64_t contract_fixed_bytes = 606;
    constexpr uint64_t storage_slot_bytes = 352;

    eosio::check(gas_per_byte_f >= 0.0, "gas per byte can not be negative");
    eosio::check(gas_per_byte_f * contract_fixed_bytes < (double)(0x7ffffffffffull), "gas per byte excceed limit");

    uint64_t gas_per_byte = (uint64_t)(gas_per_byte_f + 1.0);

    param.pending = gas_parameter_type::gas_parameter_data_v1 {
        .gas_txnewaccount = account_bytes * gas_per_byte,
        .gas_newaccount = account_bytes * gas_per_byte,
        .gas_txcreate = contract_fixed_bytes * gas_per_byte,
        .gas_codedeposit = gas_per_byte,
        .gas_sset = 100 + storage_slot_bytes * gas_per_byte
    };
    param.pending_time = get_current_time();

    set_dirty();
}

std::pair<const gas_parameter_type::gas_parameter_data_type &, bool> config_wrapper::get_gas_param_maybe_update() {
    if (!_cached_config.gas_parameter.has_value()) {
        _cached_config.gas_parameter = gas_parameter_type();
        set_dirty();
        return std::pair<const gas_parameter_type::gas_parameter_data_type &, bool>(_cached_config.gas_parameter->current, false);
    }

    auto pair = _cached_config.gas_parameter->get_gas_param_maybe_update(_cached_config.genesis_time, get_current_time());

    if (pair.second) {
        set_dirty();
    }

    return pair;
}

bool config_wrapper::is_dirty()const {
    return _dirty;
}

void config_wrapper::set_dirty() {
    _dirty=true;
}

void config_wrapper::clear_dirty() {
    _dirty=false;
}

time_point config_wrapper::get_current_time()const {
    if(!current_time_point.has_value()) {
        current_time_point = eosio::current_time_point();
    }
    return current_time_point.value();
}

} //namespace evm_runtime