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
    std::shared_ptr<P2PMessage> message = nullptr;

    do
    {
        //get input message from remote node
        const std::shared_ptr<P2PMessage> message = connection->receive();

        const std::shared_ptr<P2PMessage> response = proccessMessage(message);

        //send result
        connection->send(response);
        sleep(5);
    } while(message);
    BOOST_LOG_TRIVIAL(info) << "Session: " << connection->getConnectionIdentifier() << " has finished";
}

const shared_ptr<P2PMessage> SessionManager::proccessMessage(const shared_ptr<P2PMessage> message)
{
    if(message->getType() == P2PMessage::MESSAGE_TYPE::JOIN)
        return P2PMessage::createJoinResponseMessage();

    return nullptr;
}
