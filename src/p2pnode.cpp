#include "p2pnode.h"

#include <iostream>
#include <csignal>

using namespace std;

P2PNode::P2PNode(const short remoteConnectionsPort, const short localConnectionsPort)
{
    auto registerFun = [this](std::unique_ptr<TcpConnection> conn) {sessionManager_.createSession(move(conn));};
    server_ = make_unique<TcpServer>("0.0.0.0", remoteConnectionsPort, registerFun);
    serverThread_ = std::thread([this,remoteConnectionsPort](){
        server_->run();
    });

    localConnectionsServer_ = make_unique<TcpServer>("127.0.0.1", localConnectionsPort, registerFun);
}

P2PNode::~P2PNode()
{
    cout << "Finish TCPServer thread\n";
    server_->stop();
    serverThread_.join();
}

void P2PNode::run()
{
    localConnectionsServer_->run();
    cout << "Finish P2PNode\n";
}

void P2PNode::stop(const int signal)
{
    cout << "Stop P2PNode with signal: " << signal << endl;
    localConnectionsServer_->stop();
}
