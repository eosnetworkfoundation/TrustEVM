// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: remote/ethbackend.proto

#include "remote/ethbackend.pb.h"
#include "remote/ethbackend.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace remote {

static const char* ETHBACKEND_method_names[] = {
  "/remote.ETHBACKEND/Add",
  "/remote.ETHBACKEND/Etherbase",
  "/remote.ETHBACKEND/NetVersion",
  "/remote.ETHBACKEND/ProtocolVersion",
  "/remote.ETHBACKEND/ClientVersion",
  "/remote.ETHBACKEND/Subscribe",
  "/remote.ETHBACKEND/GetWork",
  "/remote.ETHBACKEND/SubmitWork",
  "/remote.ETHBACKEND/SubmitHashRate",
  "/remote.ETHBACKEND/GetHashRate",
  "/remote.ETHBACKEND/Mining",
};

std::unique_ptr< ETHBACKEND::Stub> ETHBACKEND::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ETHBACKEND::Stub> stub(new ETHBACKEND::Stub(channel));
  return stub;
}

ETHBACKEND::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Add_(ETHBACKEND_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Etherbase_(ETHBACKEND_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_NetVersion_(ETHBACKEND_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ProtocolVersion_(ETHBACKEND_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ClientVersion_(ETHBACKEND_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Subscribe_(ETHBACKEND_method_names[5], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_GetWork_(ETHBACKEND_method_names[6], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SubmitWork_(ETHBACKEND_method_names[7], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SubmitHashRate_(ETHBACKEND_method_names[8], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetHashRate_(ETHBACKEND_method_names[9], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Mining_(ETHBACKEND_method_names[10], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ETHBACKEND::Stub::Add(::grpc::ClientContext* context, const ::remote::TxRequest& request, ::remote::AddReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Add_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::Add(::grpc::ClientContext* context, const ::remote::TxRequest* request, ::remote::AddReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Add_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Add(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::AddReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Add_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Add(::grpc::ClientContext* context, const ::remote::TxRequest* request, ::remote::AddReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Add_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::Add(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::AddReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Add_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::AddReply>* ETHBACKEND::Stub::AsyncAddRaw(::grpc::ClientContext* context, const ::remote::TxRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::AddReply>::Create(channel_.get(), cq, rpcmethod_Add_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::AddReply>* ETHBACKEND::Stub::PrepareAsyncAddRaw(::grpc::ClientContext* context, const ::remote::TxRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::AddReply>::Create(channel_.get(), cq, rpcmethod_Add_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::Etherbase(::grpc::ClientContext* context, const ::remote::EtherbaseRequest& request, ::remote::EtherbaseReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Etherbase_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::Etherbase(::grpc::ClientContext* context, const ::remote::EtherbaseRequest* request, ::remote::EtherbaseReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Etherbase_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Etherbase(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::EtherbaseReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Etherbase_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Etherbase(::grpc::ClientContext* context, const ::remote::EtherbaseRequest* request, ::remote::EtherbaseReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Etherbase_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::Etherbase(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::EtherbaseReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Etherbase_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::EtherbaseReply>* ETHBACKEND::Stub::AsyncEtherbaseRaw(::grpc::ClientContext* context, const ::remote::EtherbaseRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::EtherbaseReply>::Create(channel_.get(), cq, rpcmethod_Etherbase_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::EtherbaseReply>* ETHBACKEND::Stub::PrepareAsyncEtherbaseRaw(::grpc::ClientContext* context, const ::remote::EtherbaseRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::EtherbaseReply>::Create(channel_.get(), cq, rpcmethod_Etherbase_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::NetVersion(::grpc::ClientContext* context, const ::remote::NetVersionRequest& request, ::remote::NetVersionReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_NetVersion_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::NetVersion(::grpc::ClientContext* context, const ::remote::NetVersionRequest* request, ::remote::NetVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_NetVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::NetVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::NetVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_NetVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::NetVersion(::grpc::ClientContext* context, const ::remote::NetVersionRequest* request, ::remote::NetVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_NetVersion_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::NetVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::NetVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_NetVersion_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::NetVersionReply>* ETHBACKEND::Stub::AsyncNetVersionRaw(::grpc::ClientContext* context, const ::remote::NetVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::NetVersionReply>::Create(channel_.get(), cq, rpcmethod_NetVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::NetVersionReply>* ETHBACKEND::Stub::PrepareAsyncNetVersionRaw(::grpc::ClientContext* context, const ::remote::NetVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::NetVersionReply>::Create(channel_.get(), cq, rpcmethod_NetVersion_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::ProtocolVersion(::grpc::ClientContext* context, const ::remote::ProtocolVersionRequest& request, ::remote::ProtocolVersionReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ProtocolVersion_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::ProtocolVersion(::grpc::ClientContext* context, const ::remote::ProtocolVersionRequest* request, ::remote::ProtocolVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ProtocolVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::ProtocolVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::ProtocolVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ProtocolVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::ProtocolVersion(::grpc::ClientContext* context, const ::remote::ProtocolVersionRequest* request, ::remote::ProtocolVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ProtocolVersion_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::ProtocolVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::ProtocolVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ProtocolVersion_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::ProtocolVersionReply>* ETHBACKEND::Stub::AsyncProtocolVersionRaw(::grpc::ClientContext* context, const ::remote::ProtocolVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::ProtocolVersionReply>::Create(channel_.get(), cq, rpcmethod_ProtocolVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::ProtocolVersionReply>* ETHBACKEND::Stub::PrepareAsyncProtocolVersionRaw(::grpc::ClientContext* context, const ::remote::ProtocolVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::ProtocolVersionReply>::Create(channel_.get(), cq, rpcmethod_ProtocolVersion_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::ClientVersion(::grpc::ClientContext* context, const ::remote::ClientVersionRequest& request, ::remote::ClientVersionReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ClientVersion_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::ClientVersion(::grpc::ClientContext* context, const ::remote::ClientVersionRequest* request, ::remote::ClientVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ClientVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::ClientVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::ClientVersionReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ClientVersion_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::ClientVersion(::grpc::ClientContext* context, const ::remote::ClientVersionRequest* request, ::remote::ClientVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ClientVersion_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::ClientVersion(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::ClientVersionReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ClientVersion_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::ClientVersionReply>* ETHBACKEND::Stub::AsyncClientVersionRaw(::grpc::ClientContext* context, const ::remote::ClientVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::ClientVersionReply>::Create(channel_.get(), cq, rpcmethod_ClientVersion_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::ClientVersionReply>* ETHBACKEND::Stub::PrepareAsyncClientVersionRaw(::grpc::ClientContext* context, const ::remote::ClientVersionRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::ClientVersionReply>::Create(channel_.get(), cq, rpcmethod_ClientVersion_, context, request, false);
}

::grpc::ClientReader< ::remote::SubscribeReply>* ETHBACKEND::Stub::SubscribeRaw(::grpc::ClientContext* context, const ::remote::SubscribeRequest& request) {
  return ::grpc_impl::internal::ClientReaderFactory< ::remote::SubscribeReply>::Create(channel_.get(), rpcmethod_Subscribe_, context, request);
}

void ETHBACKEND::Stub::experimental_async::Subscribe(::grpc::ClientContext* context, ::remote::SubscribeRequest* request, ::grpc::experimental::ClientReadReactor< ::remote::SubscribeReply>* reactor) {
  ::grpc_impl::internal::ClientCallbackReaderFactory< ::remote::SubscribeReply>::Create(stub_->channel_.get(), stub_->rpcmethod_Subscribe_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::remote::SubscribeReply>* ETHBACKEND::Stub::AsyncSubscribeRaw(::grpc::ClientContext* context, const ::remote::SubscribeRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc_impl::internal::ClientAsyncReaderFactory< ::remote::SubscribeReply>::Create(channel_.get(), cq, rpcmethod_Subscribe_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::remote::SubscribeReply>* ETHBACKEND::Stub::PrepareAsyncSubscribeRaw(::grpc::ClientContext* context, const ::remote::SubscribeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncReaderFactory< ::remote::SubscribeReply>::Create(channel_.get(), cq, rpcmethod_Subscribe_, context, request, false, nullptr);
}

::grpc::Status ETHBACKEND::Stub::GetWork(::grpc::ClientContext* context, const ::remote::GetWorkRequest& request, ::remote::GetWorkReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetWork_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::GetWork(::grpc::ClientContext* context, const ::remote::GetWorkRequest* request, ::remote::GetWorkReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetWork_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::GetWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::GetWorkReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetWork_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::GetWork(::grpc::ClientContext* context, const ::remote::GetWorkRequest* request, ::remote::GetWorkReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetWork_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::GetWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::GetWorkReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetWork_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::GetWorkReply>* ETHBACKEND::Stub::AsyncGetWorkRaw(::grpc::ClientContext* context, const ::remote::GetWorkRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::GetWorkReply>::Create(channel_.get(), cq, rpcmethod_GetWork_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::GetWorkReply>* ETHBACKEND::Stub::PrepareAsyncGetWorkRaw(::grpc::ClientContext* context, const ::remote::GetWorkRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::GetWorkReply>::Create(channel_.get(), cq, rpcmethod_GetWork_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::SubmitWork(::grpc::ClientContext* context, const ::remote::SubmitWorkRequest& request, ::remote::SubmitWorkReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_SubmitWork_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::SubmitWork(::grpc::ClientContext* context, const ::remote::SubmitWorkRequest* request, ::remote::SubmitWorkReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SubmitWork_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::SubmitWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::SubmitWorkReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SubmitWork_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::SubmitWork(::grpc::ClientContext* context, const ::remote::SubmitWorkRequest* request, ::remote::SubmitWorkReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_SubmitWork_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::SubmitWork(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::SubmitWorkReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_SubmitWork_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::SubmitWorkReply>* ETHBACKEND::Stub::AsyncSubmitWorkRaw(::grpc::ClientContext* context, const ::remote::SubmitWorkRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::SubmitWorkReply>::Create(channel_.get(), cq, rpcmethod_SubmitWork_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::SubmitWorkReply>* ETHBACKEND::Stub::PrepareAsyncSubmitWorkRaw(::grpc::ClientContext* context, const ::remote::SubmitWorkRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::SubmitWorkReply>::Create(channel_.get(), cq, rpcmethod_SubmitWork_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::SubmitHashRate(::grpc::ClientContext* context, const ::remote::SubmitHashRateRequest& request, ::remote::SubmitHashRateReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_SubmitHashRate_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::SubmitHashRate(::grpc::ClientContext* context, const ::remote::SubmitHashRateRequest* request, ::remote::SubmitHashRateReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SubmitHashRate_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::SubmitHashRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::SubmitHashRateReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SubmitHashRate_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::SubmitHashRate(::grpc::ClientContext* context, const ::remote::SubmitHashRateRequest* request, ::remote::SubmitHashRateReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_SubmitHashRate_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::SubmitHashRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::SubmitHashRateReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_SubmitHashRate_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::SubmitHashRateReply>* ETHBACKEND::Stub::AsyncSubmitHashRateRaw(::grpc::ClientContext* context, const ::remote::SubmitHashRateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::SubmitHashRateReply>::Create(channel_.get(), cq, rpcmethod_SubmitHashRate_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::SubmitHashRateReply>* ETHBACKEND::Stub::PrepareAsyncSubmitHashRateRaw(::grpc::ClientContext* context, const ::remote::SubmitHashRateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::SubmitHashRateReply>::Create(channel_.get(), cq, rpcmethod_SubmitHashRate_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::GetHashRate(::grpc::ClientContext* context, const ::remote::GetHashRateRequest& request, ::remote::GetHashRateReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_GetHashRate_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::GetHashRate(::grpc::ClientContext* context, const ::remote::GetHashRateRequest* request, ::remote::GetHashRateReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetHashRate_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::GetHashRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::GetHashRateReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_GetHashRate_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::GetHashRate(::grpc::ClientContext* context, const ::remote::GetHashRateRequest* request, ::remote::GetHashRateReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetHashRate_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::GetHashRate(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::GetHashRateReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_GetHashRate_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::GetHashRateReply>* ETHBACKEND::Stub::AsyncGetHashRateRaw(::grpc::ClientContext* context, const ::remote::GetHashRateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::GetHashRateReply>::Create(channel_.get(), cq, rpcmethod_GetHashRate_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::GetHashRateReply>* ETHBACKEND::Stub::PrepareAsyncGetHashRateRaw(::grpc::ClientContext* context, const ::remote::GetHashRateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::GetHashRateReply>::Create(channel_.get(), cq, rpcmethod_GetHashRate_, context, request, false);
}

::grpc::Status ETHBACKEND::Stub::Mining(::grpc::ClientContext* context, const ::remote::MiningRequest& request, ::remote::MiningReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Mining_, context, request, response);
}

void ETHBACKEND::Stub::experimental_async::Mining(::grpc::ClientContext* context, const ::remote::MiningRequest* request, ::remote::MiningReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Mining_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Mining(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::MiningReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Mining_, context, request, response, std::move(f));
}

void ETHBACKEND::Stub::experimental_async::Mining(::grpc::ClientContext* context, const ::remote::MiningRequest* request, ::remote::MiningReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Mining_, context, request, response, reactor);
}

void ETHBACKEND::Stub::experimental_async::Mining(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::remote::MiningReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Mining_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::remote::MiningReply>* ETHBACKEND::Stub::AsyncMiningRaw(::grpc::ClientContext* context, const ::remote::MiningRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::MiningReply>::Create(channel_.get(), cq, rpcmethod_Mining_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::remote::MiningReply>* ETHBACKEND::Stub::PrepareAsyncMiningRaw(::grpc::ClientContext* context, const ::remote::MiningRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::remote::MiningReply>::Create(channel_.get(), cq, rpcmethod_Mining_, context, request, false);
}

ETHBACKEND::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::TxRequest, ::remote::AddReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::TxRequest* req,
             ::remote::AddReply* resp) {
               return service->Add(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::EtherbaseRequest, ::remote::EtherbaseReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::EtherbaseRequest* req,
             ::remote::EtherbaseReply* resp) {
               return service->Etherbase(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::NetVersionRequest, ::remote::NetVersionReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::NetVersionRequest* req,
             ::remote::NetVersionReply* resp) {
               return service->NetVersion(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::ProtocolVersionRequest, ::remote::ProtocolVersionReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::ProtocolVersionRequest* req,
             ::remote::ProtocolVersionReply* resp) {
               return service->ProtocolVersion(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::ClientVersionRequest, ::remote::ClientVersionReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::ClientVersionRequest* req,
             ::remote::ClientVersionReply* resp) {
               return service->ClientVersion(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[5],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< ETHBACKEND::Service, ::remote::SubscribeRequest, ::remote::SubscribeReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::SubscribeRequest* req,
             ::grpc_impl::ServerWriter<::remote::SubscribeReply>* writer) {
               return service->Subscribe(ctx, req, writer);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[6],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::GetWorkRequest, ::remote::GetWorkReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::GetWorkRequest* req,
             ::remote::GetWorkReply* resp) {
               return service->GetWork(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[7],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::SubmitWorkRequest, ::remote::SubmitWorkReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::SubmitWorkRequest* req,
             ::remote::SubmitWorkReply* resp) {
               return service->SubmitWork(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[8],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::SubmitHashRateRequest, ::remote::SubmitHashRateReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::SubmitHashRateRequest* req,
             ::remote::SubmitHashRateReply* resp) {
               return service->SubmitHashRate(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[9],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::GetHashRateRequest, ::remote::GetHashRateReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::GetHashRateRequest* req,
             ::remote::GetHashRateReply* resp) {
               return service->GetHashRate(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ETHBACKEND_method_names[10],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ETHBACKEND::Service, ::remote::MiningRequest, ::remote::MiningReply>(
          [](ETHBACKEND::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::remote::MiningRequest* req,
             ::remote::MiningReply* resp) {
               return service->Mining(ctx, req, resp);
             }, this)));
}

ETHBACKEND::Service::~Service() {
}

::grpc::Status ETHBACKEND::Service::Add(::grpc::ServerContext* context, const ::remote::TxRequest* request, ::remote::AddReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::Etherbase(::grpc::ServerContext* context, const ::remote::EtherbaseRequest* request, ::remote::EtherbaseReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::NetVersion(::grpc::ServerContext* context, const ::remote::NetVersionRequest* request, ::remote::NetVersionReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::ProtocolVersion(::grpc::ServerContext* context, const ::remote::ProtocolVersionRequest* request, ::remote::ProtocolVersionReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::ClientVersion(::grpc::ServerContext* context, const ::remote::ClientVersionRequest* request, ::remote::ClientVersionReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::Subscribe(::grpc::ServerContext* context, const ::remote::SubscribeRequest* request, ::grpc::ServerWriter< ::remote::SubscribeReply>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::GetWork(::grpc::ServerContext* context, const ::remote::GetWorkRequest* request, ::remote::GetWorkReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::SubmitWork(::grpc::ServerContext* context, const ::remote::SubmitWorkRequest* request, ::remote::SubmitWorkReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::SubmitHashRate(::grpc::ServerContext* context, const ::remote::SubmitHashRateRequest* request, ::remote::SubmitHashRateReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::GetHashRate(::grpc::ServerContext* context, const ::remote::GetHashRateRequest* request, ::remote::GetHashRateReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ETHBACKEND::Service::Mining(::grpc::ServerContext* context, const ::remote::MiningRequest* request, ::remote::MiningReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace remote

