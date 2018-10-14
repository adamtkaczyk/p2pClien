#include "p2pnode.h"
#include "boost/log/trivial.hpp"

#include <iostream>
#include <csignal>

using namespace std;

P2PNode::P2PNode(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort)
{
    sessionManager_ = make_unique<SessionManager>(routingTable_);

    initInputServers(remoteConnectionsPort,localConnectionsPort);
}

P2PNode::P2PNode(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort, const string bootingNodeIp, const unsigned bootingNodePort)
{
    sessionManager_ = make_unique<SessionManager>(routingTable_);

    bootToNetwork(bootingNodeIp,bootingNodePort);
    initInputServers(remoteConnectionsPort,localConnectionsPort);
}

P2PNode::~P2PNode()
{
    BOOST_LOG_TRIVIAL(info) << "Finish TCPServer thread";
    server_->stop();
    serverThread_.join();
}

void P2PNode::initInputServers(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort)
{
    auto registerFun = [this](std::unique_ptr<TcpConnection> conn) {sessionManager_->createSession(move(conn));};
    server_ = make_unique<TcpServer>("0.0.0.0", remoteConnectionsPort, registerFun);
    serverThread_ = std::thread([this,remoteConnectionsPort](){
        server_->run();
    });

    localConnectionsServer_ = make_unique<TcpServer>("127.0.0.1", localConnectionsPort, registerFun);
}

void P2PNode::bootToNetwork(const std::string bootingNodeIp, const unsigned bootingNodePort)
{
    unique_ptr<TcpConnection> conn = make_unique<TcpConnection>(bootingNodeIp,bootingNodePort);
    conn->connect();
    conn->send("join");
    conn->receive();
}

void P2PNode::run()
{
    localConnectionsServer_->run();
    BOOST_LOG_TRIVIAL(info) << "Finish P2PNode";
}

void P2PNode::stop(const int signal)
{
    BOOST_LOG_TRIVIAL(info) << "Stop P2PNode with signal: " << signal;
    localConnectionsServer_->stop();
}
