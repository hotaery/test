#include <echo_server.pb.h>
#include <brpc/channel.h>

int main() {
    brpc::ChannelOptions options;
    brpc::Channel channel;
    options.protocol = "baidu_std";
    if (channel.Init("127.0.0.1:8080", &options) != 0) {
        LOG(INFO) << "Failed to init channel";
        return -1;
    }
    echo::EchoServer_Stub stub(&channel);
    echo::EchoRequest req;
    echo::EchoResponse resp;
    req.set_txt("hello world");
    brpc::Controller cntl;
    stub.Echo(&cntl, &req, &resp, NULL);
    LOG(INFO) << "resp: " << resp.txt();
    return 0;
}