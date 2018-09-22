#ifndef REMOTENODE_H
#define REMOTENODE_H

#include "networking/tcpconnection.h"

#include <string>
#include <memory>

class RemoteNode
{
public:
    RemoteNode(const std::string ipAddress, const short port);

    //std::unique_ptr<TcpConnection> connect();
private:
    const std::string ipAddress_;
    const short port_;
};

#endif // REMOTENODE_H
