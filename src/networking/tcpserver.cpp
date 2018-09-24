#include "tcpserver.h"

#include <boost/bind.hpp>
#include <functional>
#include <iostream>

using namespace std;

TcpServer::TcpServer(const short port, RegisterFunction registerConnection)
    : acceptor_(ioContext_, tcp::endpoint(tcp::v4(),port)), regsiterConnection_(registerConnection)
{
    startAccept();
}

void TcpServer::startAccept()
{
    acceptor_.async_accept([this](boost::system::error_code error, tcp::socket socket)
    {
        auto connection = make_unique<TcpConnection>(move(socket));
        if(!error)
            regsiterConnection_(move(connection));
        startAccept();
    });
}
