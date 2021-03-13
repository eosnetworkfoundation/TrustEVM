/*
    Copyright 2020 The Silkrpc Authors

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "connection_manager.hpp"

#include <memory>

namespace silkrpc::http {

ConnectionManager::ConnectionManager() {
}

asio::awaitable<void> ConnectionManager::start(std::shared_ptr<Connection> c) {
    connections_.insert(c);
    co_await c->start();
}

void ConnectionManager::stop(std::shared_ptr<Connection> c) {
    connections_.erase(c);
    c->stop();
}

void ConnectionManager::stop_all() {
    for (auto c : connections_) {
        c->stop();
    }
    connections_.clear();
}

} // namespace silkrpc::http