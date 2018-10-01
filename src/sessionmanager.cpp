#include "sessionmanager.h"

#include <unistd.h>
#include <iostream>

using namespace std;

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
    end_ = true;
    cout << "Waiting for finishing all open session\n";
    for(auto& t : openSessions_)
        t.second.wait();
}

void SessionManager::createSession(std::unique_ptr<P2PConnection> connection)
{
    string key = connection->getConnectionIdentifier();

    //start new asyns task from connection
    auto task = [this, conn = move(connection)]() mutable { sessionThread(std::move(conn)); };
    //save future result in map
    openSessions_[key] = std::async(std::launch::async, move(task));

    //clear old session from map
    clearFinishedSessions();
}

void SessionManager::sessionThread(std::unique_ptr<P2PConnection> connection)
{
    cout << "Start session: " << connection->getConnectionIdentifier() << endl;
    std::unique_ptr<P2PMessage> message = nullptr;

    do
    {
        //get input message from remote node
        std::unique_ptr<P2PMessage> message = connection->receive();

        //TODO: Process message

        //send result
        connection->send("Result message\n");
        sleep(5);
    }
    while(message);
    cout << "Session: " << connection->getConnectionIdentifier() << " has finished" << endl;
}

void SessionManager::clearFinishedSessions()
{
    auto session = openSessions_.cbegin();
    while(session != openSessions_.cend())
    {
        //if session is finished remove from map
        if(session->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            cout << "Remove session: " << session->first << " from map" << endl;
            session = openSessions_.erase(session);
        }
        else
            session++;
    }
}
