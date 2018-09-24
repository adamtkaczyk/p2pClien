#include "p2pnode.h"

#include <iostream>

using namespace std;

P2PNode::P2PNode(const short port)
{
    serverThread_ = std::thread([this,port](){
        server_ = make_unique<TcpServer>(port, [this](std::unique_ptr<TcpConnection> conn) {sessionManager_.createSession(move(conn));});
        server_->run();
    });
}

P2PNode::~P2PNode()
{
    serverThread_.join();
}

void P2PNode::run()
{
    while(true)
    {
        //TODO: get data from input
        //TODO: send request
        //TODO: return result
        sleep(1);
        cout << "run\n";
    }
}
