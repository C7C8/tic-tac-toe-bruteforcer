#include <iostream>
#include <vector>
using namespace std;

const unsigned short int GRID_X = 3;
const unsigned short int GRID_Y = 3;

class Node
{
public:
    Node();
protected:
    uint8_t board[GRID_X][GRID_Y];
};
