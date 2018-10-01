#include <iostream>
#include <memory>

#include "p2pnode.h"

using namespace std;

std::unique_ptr<P2PNode> p2pNode = nullptr;

int main()
{
    //create node object
    p2pNode = std::make_unique<P2PNode>(9876,9877);
    //register handler function
    std::signal(SIGINT, [](int signal){ p2pNode->stop(signal); });
    //run node
    p2pNode->run();

    return 0;
}
