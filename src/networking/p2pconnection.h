#ifndef P2PCONNECTION_H
#define P2PCONNECTION_H

#include "protocol/p2pmessage.h"

#include <memory>

class P2PConnectionException : public std::runtime_error
{
public:
    P2PConnectionException(std::string message) : std::runtime_error(message) {}
};

class P2PConnection
{
public:
    P2PConnection();
    //receive next P2PMessage
    virtual std::unique_ptr<P2PMessage> receive() = 0;
    //send P2PMessage
    virtual void send(std::unique_ptr<P2PMessage> message) = 0;
    //send simple text message
    virtual void send(std::string message) = 0;
    //get string which is unique for this connection
    virtual std::string getConnectionIdentifier() = 0;
};

#endif // P2PCONNECTION_H
