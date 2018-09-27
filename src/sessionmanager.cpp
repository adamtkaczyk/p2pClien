#include "sessionmanager.h"

#include <unistd.h>
#include <iostream>

using namespace std;

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
    cout << "Waiting for finishing all open session\n";
    for(auto& t : openSessions_)
        t.second.wait();
}

void SessionManager::createSession(std::unique_ptr<P2PConnection> connection)
{
    string key = connection->getConnectionIdentifier();
    //start new asyns task from connection
    auto future = std::async(std::launch::async, [this, conn = move(connection)]() mutable { sessionThread(std::move(conn)); });
    //save future result
    openSessions_[key] = move(future);
}

void SessionManager::sessionThread(std::unique_ptr<P2PConnection> connection)
{
    for(int i = 0; i < 10; i++)
    {
        //get input message from remote node
        auto message = connection->receive();

        //TODO: Process message

        //send result
        connection->send("Message\n");
        sleep(5);
    }
}

void SessionManager::clearFinishedSessions()
{
    auto session = openSessions_.cbegin();
    while(session != openSessions_.cend())
    {
        //if session is finished remove from map
        if(session->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            cout << "Found finished thread: " << session->first << endl;
            session = openSessions_.erase(session);
        }
        else
            session++;
    }
}
