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
    //Input remote connection connection server
    std::unique_ptr<TcpServer> server_;
    //Thread from input remove server
    std::thread serverThread_;
    //attribute indicate if proccess should finish
    static bool end_;

    //TODO: data source

    //TODO: data destination

    //TODO: Routing table

    static void signalHandler(int signal);
};

#endif // P2PNODE_H
