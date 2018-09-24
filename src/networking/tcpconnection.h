#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpConnection
{
public:
    TcpConnection(tcp::socket socket);
    ~TcpConnection();

    tcp::socket& getSocket() { return socket_; }

    void send(std::string message) { socket_.send(boost::asio::buffer(message)); }
private:
    tcp::socket socket_;
};

#endif // TCPCONNECTION_H
