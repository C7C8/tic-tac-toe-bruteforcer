#include <iostream>
#include <cstdlib>
#include "Node.h"
using namespace std;

#define ON_DEBUGGER

int main()
{
    cout << "Starting calculations..." << endl;
    Node rootNode;
    rootNode.solveForChildren();
    cout << "Number of nodes: " << rootNode.getCount() << endl;
    cout << "X Wins:\t" << rootNode.getXCount() << endl;
    cout << "O Wins:\t" << rootNode.getOCount() << endl;
    cout << "Ties:\t" << rootNode.getTieCount() << endl;
    cout << "Sum:\t" << rootNode.getTieCount() + rootNode.getXCount() + rootNode.getOCount() << endl;

    #ifndef ON_DEBUGGER
        system("pause");
    #endif // ON_DEBUGGER
}
