#ifndef P2PNODE_H
#define P2PNODE_H

#include "networking/tcpserver.h"
#include "sessionmanager.h"

#include <memory>
#include <thread>

class P2PNode
{
public:
    P2PNode(const short remoteConnectionsPort, const short localConnectionsPort);
    ~P2PNode();

    void run();

    void stop(const int signal);
private:
    SessionManager sessionManager_;
    //Input remote connection server
    std::unique_ptr<TcpServer> server_;
    //Thread from input remove server
    std::thread serverThread_;
    //Input local connection server
    std::unique_ptr<TcpServer> localConnectionsServer_;
};

#endif // P2PNODE_H
