#include <iostream>
#include "Node.h"
using namespace std;

int main()
{
    cout << "Hello, world!" << endl;
    Node rootNode;
    rootNode.solveForChildren();
    cout << "Number of nodes: " << rootNode.getCount() << endl;
    cout << "X Wins:\t" << rootNode.getXCount() << endl;
    cout << "O Wins:\t" << rootNode.getOCount() << endl;
    cout << "Ties:\t" << rootNode.getTieCount() << endl;
    cout << "Sum:\t" << rootNode.getTieCount() + rootNode.getXCount() + rootNode.getOCount() << endl;
}
