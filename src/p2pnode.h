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
private:
    SessionManager sessionManager_;

    std::thread serverThread_;
    std::unique_ptr<TcpServer> server_;

    //TODO: data source

    //TODO: data destination

    //TODO: Routing table
};

#endif // P2PNODE_H
