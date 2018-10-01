#include "tcpserver.h"

#include <boost/bind.hpp>
#include <functional>
#include <iostream>

using namespace std;

TcpServer::TcpServer(const string ip, const short port, const RegisterFunction registerConnection)
    : acceptor_(ioContext_, tcp::endpoint(boost::asio::ip::address::from_string(ip),port)), regsiterConnection_(registerConnection)
{
    startAccept();
}

void TcpServer::startAccept()
{
    acceptor_.async_accept([this](boost::system::error_code error, tcp::socket socket)
    {
        auto connection = make_unique<TcpConnection>(move(socket));
        if(!error && regsiterConnection_)
            regsiterConnection_(move(connection));
        else
            cout << "ERROR\n";
        startAccept();
    });
}
