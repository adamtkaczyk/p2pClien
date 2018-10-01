#include "tcpconnection.h"

#include <iostream>

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket) : socket_(move(socket))
{
    cout << "Create new TCP connection ip:port=[" << getConnectionIdentifier() << "]" << endl;
}

TcpConnection::~TcpConnection()
{
    socket_.close();
    cout << "Finish TCP Connection\n";
}

std::unique_ptr<P2PMessage> TcpConnection::receive()
{
    return nullptr;//make_unique<P2PMessage>();
}

void TcpConnection::send(std::unique_ptr<P2PMessage> message)
{

}

void TcpConnection::send(std::string message)
{
    try
    {
        socket_.send(boost::asio::buffer(message));
    }
    catch(boost::system::system_error& e)
    {
        throw P2PConnectionException(e.what());
    }
}

std::string TcpConnection::getConnectionIdentifier()
{
    return socket_.remote_endpoint().address().to_string() + ":" + std::to_string(socket_.remote_endpoint().port());
}
