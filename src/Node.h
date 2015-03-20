#pragma once

#include <iostream>
#include <vector>
using namespace std;

const unsigned short int GRID_X = 3;
const unsigned short int GRID_Y = 3;

const uint8_t X = 0;
const uint8_t O = 1;
enum endType {XWIN, OWIN, TIE};

class Node
{
public:
    Node();
    void solveForChildren();
    endType getEndType() const;

    uint8_t getXCount() const;
    uint8_t getOCount() const;
    uint8_t getTieCount() const;
    void incrXCount();
    void incrOCount();
    void incrTieCount();
protected:
    uint8_t xCount;
    uint8_t oCount;
    uint8_t tieCount;

    Node* previous;
    static int count;

    uint8_t board[GRID_X][GRID_Y];
    vector<Node> children;
};
