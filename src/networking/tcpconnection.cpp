#include "tcpconnection.h"
#include "boost/log/trivial.hpp"

#include <iostream>

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket)
    : socket_(move(socket)), ip_(socket_.remote_endpoint().address().to_string()), port_(socket_.remote_endpoint().port())
{
    BOOST_LOG_TRIVIAL(info) << "Create new TCP connection ip:port=[" << getConnectionIdentifier() << "]";
}

TcpConnection::TcpConnection(const std::string ip, const unsigned port) : ip_(ip), port_(port), socket_(ioService_)
{
}

TcpConnection::~TcpConnection()
{
    socket_.close();
    BOOST_LOG_TRIVIAL(info) << "Finish TCP Connection";
}

void TcpConnection::connect()
{
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip_), port_);
    socket_.connect(endpoint);
}

const std::unique_ptr<P2PMessage> TcpConnection::receive()
{
    return nullptr;//make_unique<P2PMessage>();
}

void TcpConnection::send(const std::unique_ptr<P2PMessage> message)
{

}

void TcpConnection::send(const std::string message)
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

const std::string TcpConnection::getConnectionIdentifier() const
{
    return ip_ + ":" + std::to_string(port_);
}
