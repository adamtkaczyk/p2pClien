#ifndef P2PNODE_H
#define P2PNODE_H

#include "networking/tcpserver.h"
#include "sessionmanager.h"

#include <memory>
#include <thread>

class P2PNode
{
public:
    P2PNode(const short port);
    ~P2PNode();

    void run();

    void stop() {end_ = true;}
private:
    SessionManager sessionManager_;

    std::thread serverThread_;
    std::unique_ptr<TcpServer> server_;
    static bool end_;

    //TODO: data source

    //TODO: data destination

    //TODO: Routing table

    static void signalHandler(int signal);
};

#endif // P2PNODE_H
