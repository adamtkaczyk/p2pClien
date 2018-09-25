#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpconnection.h"

#include <memory>
#include <functional>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpServer
{
public:
    using RegisterFunction = std::function<void(std::unique_ptr<TcpConnection>)>;

    TcpServer(const short port, RegisterFunction registerConnection);
    //start TCP server
    void run() { ioContext_.run(); }
    //stop TCP server
    void stop() { ioContext_.stop(); }
private:
    boost::asio::io_context ioContext_;
    tcp::acceptor acceptor_;
    //function which register new TCP connection
    RegisterFunction regsiterConnection_;

    void startAccept();
};

#endif // TCPSERVER_H
