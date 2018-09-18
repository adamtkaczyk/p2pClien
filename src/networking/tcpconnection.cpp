#include "tcpconnection.h"

using namespace std;

TcpConnection::TcpConnection(tcp::socket socket) : socket_(move(socket))
{

}
