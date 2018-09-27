#include "p2pnode.h"

#include <iostream>
#include <csignal>

using namespace std;

bool P2PNode::end_ = false;

P2PNode::P2PNode(const short port)
{
    serverThread_ = std::thread([this,port](){
        server_ = make_unique<TcpServer>(port, [this](std::unique_ptr<TcpConnection> conn) {sessionManager_.createSession(move(conn));});
        server_->run();
    });

    std::signal(SIGINT, P2PNode::signalHandler);
}

P2PNode::~P2PNode()
{
    cout << "Finish TCPServer thread\n";
    server_->stop();
    serverThread_.join();
}

void P2PNode::signalHandler(int signal)
{
    cout << "Catch signal: " << signal << endl;
    end_ = true;
}

void P2PNode::run()
{
    while(!end_)
    {
        //TODO: get data from input
        //TODO: send request
        //TODO: return result
        sessionManager_.clearFinishedSessions();
        cout << "run " << sessionManager_.count() << " TCP session\n";
        sleep(1);
    }

    cout << "Finish P2PNode\n";
}
