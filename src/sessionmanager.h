#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "networking/p2pconnection.h"

#include <thread>
#include <future>
#include <unordered_map>

class SessionManager
{
public:
    SessionManager();
    ~SessionManager();
    //methond start new session
    void createSession(std::unique_ptr<P2PConnection> connection);
    //check and close all finished session
    void clearFinishedSessions();
    //return number od open session
    unsigned int count() const { return openSessions_.size(); }
private:
    //session thread
    void sessionThread(std::unique_ptr<P2PConnection> connection);
    //map of all running thread
    std::unordered_map<std::string,std::future<void>> openSessions_;
    bool end_ = false;
};

#endif // SESSIONMANAGER_H
