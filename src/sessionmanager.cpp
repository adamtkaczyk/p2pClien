#include "sessionmanager.h"
#include <iostream>

using namespace std;

SessionManager::SessionManager()
{
}

SessionManager::~SessionManager()
{
    for(auto& t : openThreads_)
        t.second.join();
}

void SessionManager::createSession(std::unique_ptr<TcpConnection> tcpConnection)
{
    std::thread connectionThread([this, conn = move(tcpConnection)]() mutable { sessionThread(std::move(conn)); });
    openThreads_["1"] = move(connectionThread);
}

void SessionManager::sessionThread(std::unique_ptr<TcpConnection> tcpConnection)
{
    for(int i = 0; i < 10; i++)
    {
        tcpConnection->send("Message\n");
        sleep(5);
    }
}
