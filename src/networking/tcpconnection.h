#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

#include "p2pconnection.h"

using boost::asio::ip::tcp;

class TcpConnection : public P2PConnection
{
public:
    TcpConnection(tcp::socket socket);
    ~TcpConnection();

    //get connection socket
    tcp::socket& getSocket() { return socket_; }
    //receive next P2PMessage
    virtual std::unique_ptr<P2PMessage> receive();
    //send P2PMessage
    virtual void send(std::unique_ptr<P2PMessage> message);
    //send simple text message
    virtual void send(std::string message) { socket_.send(boost::asio::buffer(message)); }
    //get string which is unique for this connection
    virtual std::string getConnectionIdentifier();
private:
    tcp::socket socket_;
};

#endif // TCPCONNECTION_H
