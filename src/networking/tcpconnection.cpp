#include "tcpconnection.h"

#include <iostream>

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket) : socket_(move(socket))
{
    cout << "New connection: " << getConnectionIdentifier()  << endl;
}

TcpConnection::~TcpConnection()
{
    socket_.close();
    cout << "Finish TCP Connection\n";
}

std::unique_ptr<P2PMessage> TcpConnection::receive()
{
    return make_unique<P2PMessage>();
}

void TcpConnection::send(std::unique_ptr<P2PMessage> message)
{

}

std::string TcpConnection::getConnectionIdentifier()
{
    return socket_.remote_endpoint().address().to_string() + ":" + std::to_string(socket_.remote_endpoint().port());
}
