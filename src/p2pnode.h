#ifndef P2PNODE_H
#define P2PNODE_H

#include "networking/tcpserver.h"
#include "sessionmanager.h"

#include <memory>
#include <thread>

class P2PNode
{
public:
    P2PNode(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort);
    P2PNode(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort, const std::string bootingNodeIp, const unsigned bootingNodePort);
    P2PNode(const P2PNode&) = delete;
    P2PNode& operator=(const P2PNode&) = delete;
    ~P2PNode();

    void run();

    void stop(const int signal);
private:
    std::shared_ptr<RoutingTable> routingTable_;
    std::unique_ptr<SessionManager> sessionManager_;
    //Input remote connection server
    std::unique_ptr<TcpServer> server_;
    //Thread from input remove server
    std::thread serverThread_;
    //Input local connection server
    std::unique_ptr<TcpServer> localConnectionsServer_;
    //Start listining input connection
    void initInputServers(const unsigned remoteConnectionsPort, const unsigned localConnectionsPort);
    //Boot node to exists network
    void bootToNetwork(const std::string bootingNodeIp, const unsigned bootingNodePort);
};

#endif // P2PNODE_H
