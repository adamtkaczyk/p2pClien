#include "tcpconnection.h"

#include <iostream>

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket) : socket_(move(socket))
{
    send("New connection\n");
}

TcpConnection::~TcpConnection()
{
    socket_.close();
    cout << "Finish TCP Connection\n";
}
