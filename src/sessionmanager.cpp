#include "sessionmanager.h"
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

void SessionManager::createSession(std::unique_ptr<TcpConnection> tcpConnection)
{
    auto future = std::async(std::launch::async, [this, conn = move(tcpConnection)]() mutable { sessionThread(std::move(conn)); });
    openSessions_["1"] = move(future);
}

void SessionManager::sessionThread(std::unique_ptr<TcpConnection> tcpConnection)
{
    for(int i = 0; i < 10; i++)
    {
        tcpConnection->send("Message\n");
        sleep(5);
    }
}

void SessionManager::clearFinishedSessions()
{
    auto session = openSessions_.cbegin();
    while(session != openSessions_.cend())
    {
        if(session->second.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
        {
            cout << "Found finished thread\n";
            session = openSessions_.erase(session);
        }
        else
            session++;
    }
}
