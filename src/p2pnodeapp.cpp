#include <iostream>
#include <memory>

#include "boost/log/trivial.hpp"

#include "p2pnode.h"

using namespace std;

std::unique_ptr<P2PNode> p2pNode = nullptr;

int main(int argc, char* argv[])
{
    BOOST_LOG_TRIVIAL(info) << "Start: " << argv[0];

    if(argc < 3)
    {
        BOOST_LOG_TRIVIAL(error) << "Wrong number of parameters";
        return 1;
    }
    const unsigned remoteConnectionsPort = stoi(argv[1]);
    const unsigned localConnectionsPort = stoi(argv[2]);

    try
    {
        //create node object
        if(argc > 4)
            p2pNode = std::make_unique<P2PNode>(remoteConnectionsPort,localConnectionsPort,argv[3],stoi(argv[4]));
        else
            p2pNode = std::make_unique<P2PNode>(remoteConnectionsPort,localConnectionsPort);
        //register handler function
        std::signal(SIGINT, [](const int signal){ p2pNode->stop(signal); });
        //run node
        p2pNode->run();
    }
    catch(std::runtime_error& e)
    {
        BOOST_LOG_TRIVIAL(error) << "Finishing process with error";
        return 1;
    }

    return 0;
}
