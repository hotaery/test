#include <echo_server.pb.h>
#include <brpc/controller.h>
#include <brpc/server.h>

namespace echo {

class EchoServerImpl : public EchoServer {
public:
    void Echo(google::protobuf::RpcController* cntl_base, 
              const EchoRequest* req,
              EchoResponse* resp,
              google::protobuf::Closure* done) {
        brpc::ClosureGuard guard(done);
        brpc::Controller* cntl = static_cast<brpc::Controller*>(cntl_base);
        LOG(INFO) << req->txt();
        resp->set_txt(req->txt());
        return;
    }
};

} // namespace echo

int main() {
    brpc::Server server;
    echo::EchoServerImpl echo_impl;
    if (server.AddService(&echo_impl, brpc::SERVER_DOESNT_OWN_SERVICE) != 0) {
        LOG(INFO) << "Failed to add service";
        return -1;
    }
    brpc::ServerOptions options;
    if (server.Start(8080, &options) < 0) {
        LOG(INFO) << "Failed to start server";
        return -1;
    }
    server.RunUntilAskedToQuit();
    return 0;
}