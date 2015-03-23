#include <iostream>
#include "Node.h"
using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    Node testNode;
    testNode.solveForChildren();
    cout << "Node count: " << testNode.getCount() << endl;
    return 0;
}
