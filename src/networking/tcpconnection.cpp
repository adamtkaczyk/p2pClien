#include "tcpconnection.h"

#include <iostream>

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket) : socket_(move(socket))
{
    socket_.send(boost::asio::buffer("New connection\n"));
}

TcpConnection::~TcpConnection()
{
    socket_.send(boost::asio::buffer("Close connection\n"));
    socket_.close();
    cout << "Koniec połączenia\n";
}
