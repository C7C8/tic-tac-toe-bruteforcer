#include <iostream>
#include <cstdlib>
#include "Node.h"
using namespace std;

int main(int argc, char* args[])
{
    cout << "Starting calculations..." << endl;
    Node rootNode;
    rootNode.first = false;
    rootNode.solveForChildren();
    cout << "Number of nodes: " << rootNode.getCount() << endl;
    cout << "X Wins:\t" << rootNode.getXCount() << endl;
    cout << "O Wins:\t" << rootNode.getOCount() << endl;
    cout << "Ties:\t" << rootNode.getTieCount() << endl;
    cout << "Sum:\t" << rootNode.getTieCount() + rootNode.getXCount() + rootNode.getOCount() << endl;

    return 0;
}
