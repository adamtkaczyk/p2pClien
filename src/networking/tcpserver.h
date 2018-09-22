#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpconnection.h"
#include "datastruct/blockingqueue.h"

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class TcpServer
{
public:
    TcpServer(const short port);
private:
    boost::asio::io_context ioContext_;
    tcp::acceptor acceptor_;
    BlockingQueue<TcpConnection>& connectionQueue_;

    void startAccept();
};

#endif // TCPSERVER_H
