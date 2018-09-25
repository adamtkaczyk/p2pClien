#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "networking/tcpconnection.h"

#include <thread>
#include <future>
#include <unordered_map>

class SessionManager
{
public:
    SessionManager();
    ~SessionManager();

    void createSession(std::unique_ptr<TcpConnection> tcpConnection);
    //check and close all finished session
    void clearFinishedSessions();
    //return number od open session
    unsigned int count() const { return openSessions_.size(); }
private:
    //session thread
    void sessionThread(std::unique_ptr<TcpConnection> tcpConnection);
    //map of all running thread
    std::unordered_map<std::string,std::future<void>> openSessions_;
};

#endif // SESSIONMANAGER_H
