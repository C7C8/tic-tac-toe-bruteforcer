#pragma once

#include <iostream>
#include <vector>
using namespace std;

const uint8_t GRID_X = 3;
const uint8_t GRID_Y = 3;
const uint8_t DIST_TO_WIN = 3; //The distance that a chain needs to cover in order to count as a win

const uint8_t PIECE_X = -1;
const uint8_t PIECE_O = 1;
enum endType {NONE, XWIN, OWIN, TIE};


class Node
{
public:
    Node();
    void solveForChildren();
    endType getEndType(uint8_t winDist = DIST_TO_WIN);
    static int getCount();

    uint8_t getXCount() const;
    uint8_t getOCount() const;
    uint8_t getTieCount() const;
    void incrXCount(int amount = 1);
    void incrOCount(int amount = 1);
    void incrTieCount(int amount = 1);
protected:
    uint8_t investigateSlot(uint8_t x, uint8_t y, uint8_t dX, uint8_t dY, uint8_t piece);

    uint8_t xCount;
    uint8_t oCount;
    uint8_t tieCount;
    uint8_t turn; //Whose turn it is RIGHT NOW. As in, ON THIS NODE!

    Node* parent;
    static int count;

    uint8_t board[GRID_X][GRID_Y];
    vector<Node> children;
};
