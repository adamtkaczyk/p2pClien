#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "networking/p2pconnection.h"
#include "algorithm/algorithm.h"

#include <thread>
#include <future>
#include <unordered_map>
#include <iostream>

class SessionManager
{
public:
    SessionManager();
    ~SessionManager();
    //methond start new session
    void createSession(std::unique_ptr<P2PConnection> connection);
    //check and close all finished session
    void clearFinishedSessions()
    {
        std::cout << "Open session: " << openSessions_.size() << std::endl;
        erase_if(openSessions_,[](auto& session) {
            return session.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        });
        std::cout << "Open session: " << openSessions_.size() << " after clean" << std::endl;
    }

    //return number od open session
    unsigned int count() const { return openSessions_.size(); }
private:
    //session thread
    void sessionTask(std::unique_ptr<P2PConnection> connection);
    //map of all future result of session
    std::unordered_map<std::string,std::future<void>> openSessions_;
};

#endif // SESSIONMANAGER_H
