#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "boost/log/trivial.hpp"
#include "networking/p2pconnection.h"
#include "algorithm/algorithm.h"
#include "routingtable.h"

#include <thread>
#include <future>
#include <unordered_map>
#include <iostream>

class SessionManager
{
public:
    SessionManager(std::shared_ptr<RoutingTable> routingTable) : routingTable_(routingTable) {}
    ~SessionManager();
    //methond start new session
    void createSession(std::unique_ptr<P2PConnection> connection);
    //check and close all finished session
    void clearFinishedSessions()
    {
        BOOST_LOG_TRIVIAL(debug) << "Open session: " << openSessions_.size();
        erase_if(openSessions_,[](auto& session) {
            return session.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        });
        BOOST_LOG_TRIVIAL(debug) << "Open session: " << openSessions_.size() << " after clean";
    }

    //return number od open session
    const unsigned int count() const { return openSessions_.size(); }
private:
    //session thread
    void sessionTask(std::unique_ptr<P2PConnection> connection);
    const std::shared_ptr<P2PMessage> proccessMessage(const std::shared_ptr<P2PMessage> message);
    //map of all future result of session
    std::unordered_map<std::string,std::future<void>> openSessions_;
    std::shared_ptr<RoutingTable> routingTable_;
};

#endif // SESSIONMANAGER_H
