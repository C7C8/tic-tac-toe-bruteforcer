#pragma once

#include <iostream>
#include "SDL_thread.h"
using namespace std;

const uint8_t GRID_X = 4;
const uint8_t GRID_Y = 4;
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

    int getXCount() const;
    int getOCount() const;
    int getTieCount() const;
    uint8_t getValue(uint8_t x, uint8_t y);
    uint8_t getTurn();
    void incrXCount(int amount = 1);
    void incrOCount(int amount = 1);
    void incrTieCount(int amount = 1);
    void setValue(uint8_t x, uint8_t y, uint8_t value);
    void setTurn(uint8_t newTurn);
protected:
    uint8_t investigateSlot(uint8_t x, uint8_t y, uint8_t dX, uint8_t dY, uint8_t piece);

    static long long unsigned int xCount;
    static long long unsigned int oCount;
    static long long unsigned int tieCount;
    uint8_t turn; //Whose turn it is RIGHT NOW. As in, ON THIS NODE!

    bool first;
    static long long unsigned int count;
    static int threadCount;
    static SDL_Thread* threads[4];

    uint8_t board[GRID_X][GRID_Y];
};
int exploreNode(void* data);
