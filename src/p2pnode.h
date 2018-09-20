#ifndef P2PNODE_H
#define P2PNODE_H

#include "networking/tcpserver.h"

#include <memory>

class P2PNode
{
public:
    P2PNode(const short port);

    void run();
private:
    std::unique_ptr<TcpServer> server_;

    //TODO: data source

    //TODO: data destination

    //TODO: Routing table
};

#endif // P2PNODE_H
