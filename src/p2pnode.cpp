#include "p2pnode.h"

#include <iostream>

using namespace std;

P2PNode::P2PNode(const short port) : server_(make_unique<TcpServer>(port))
{

}

void P2PNode::run()
{
    while(true)
    {
        //TODO: get data from input
        //TODO: send request
        //TODO: return result
        sleep(10000);
        cout << "Dupa\n";
    }
}
