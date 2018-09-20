#include <iostream>
#include <memory>

#include "p2pnode.h"

using namespace std;

int main()
{
    P2PNode p2pNode{9876};
    p2pNode.run();
    return 0;
}
