#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

#include "p2pconnection.h"

using boost::asio::ip::tcp;

class TcpConnection : public P2PConnection
{
public:
    TcpConnection(tcp::socket socket);
    TcpConnection(const std::string ip, const unsigned port);
    virtual ~TcpConnection();

    void connect();
    //get connection socket
    const tcp::socket& getSocket() { return socket_; }
    //receive next P2PMessage
    virtual const std::shared_ptr<P2PMessage> receive() override;
    //send P2PMessage
    virtual void send(const std::shared_ptr<P2PMessage> message) override;
    //send simple text message
    virtual void send(const std::string message) override;
    //get string which is unique for this connection
    virtual const std::string getConnectionIdentifier() const override;
protected:
    boost::asio::io_service ioService_;
    tcp::socket socket_;
    std::string ip_;
    unsigned port_;
};

#endif // TCPCONNECTION_H
