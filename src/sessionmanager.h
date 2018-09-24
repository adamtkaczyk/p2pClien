#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "networking/tcpconnection.h"

#include <thread>
#include <unordered_map>

class SessionManager
{
public:
    SessionManager();
    ~SessionManager();

    void createSession(std::unique_ptr<TcpConnection> tcpConnection);
private:
    //session thread
    void sessionThread(std::unique_ptr<TcpConnection> tcpConnection);
    //map of all running thread
    std::unordered_map<std::string,std::thread> openThreads_;
};

#endif // SESSIONMANAGER_H
