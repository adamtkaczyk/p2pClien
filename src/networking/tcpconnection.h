#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpConnection
{
public:
    TcpConnection(tcp::socket socket);

    tcp::socket& getSocket() { return socket_; }
private:
    tcp::socket socket_;
};

#endif // TCPCONNECTION_H
