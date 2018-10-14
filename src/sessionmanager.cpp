#include "sessionmanager.h"

#include <unistd.h>
#include <iostream>
#include <algorithm>

using namespace std;

SessionManager::~SessionManager()
{
    BOOST_LOG_TRIVIAL(info) << "Waiting for finishing all open session [" << openSessions_.size() << "]" << endl;
    for(auto& session : openSessions_)
        session.second.wait();
}

void SessionManager::createSession(std::unique_ptr<P2PConnection> connection)
{
    if(!connection)
        return;

    const string key = connection->getConnectionIdentifier();

    //create new task from connection
    auto task = [this, conn = move(connection)]() mutable { sessionTask(std::move(conn)); };
    //start task and save future result in map
    openSessions_[key] = std::async(std::launch::async, move(task));

    //clear old session from map
    clearFinishedSessions();
}

void SessionManager::sessionTask(std::unique_ptr<P2PConnection> connection)
{
    BOOST_LOG_TRIVIAL(info) << "Start session: " << connection->getConnectionIdentifier();
    std::unique_ptr<P2PMessage> message = nullptr;

    do
    {
        //get input message from remote node
        std::unique_ptr<P2PMessage> message = connection->receive();

        //TODO: Process message

        //send result
        connection->send("Result message\n");
        sleep(5);
    } while(message);
    BOOST_LOG_TRIVIAL(info) << "Session: " << connection->getConnectionIdentifier() << " has finished";
}
