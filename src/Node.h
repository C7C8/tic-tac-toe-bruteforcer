#pragma once

//#define SDL_ENABLED

#include <iostream>
#ifdef SDL_ENABLED
    #include "SDL_thread.h"
#endif // SDL_ENABLED
using namespace std;

const int GRID_X = 3;
const int GRID_Y = 3;
const int DIST_TO_WIN = 3; //The distance that a chain needs to cover in order to count as a win

const int PIECE_X = -1;
const int PIECE_O = 1;
enum endType {NONE, XWIN, OWIN, TIE};

#ifdef SDL_ENABLED
    extern SDL_SpinLock outputLock;
#endif // SDL_ENABLED

class Node
{
public:
    Node();
    void solveForChildren();
    endType getEndType(int winDist = DIST_TO_WIN);
    static int getCount();

    int getXCount() const;
    int getOCount() const;
    int getTieCount() const;
    int getValue(int x, int y);
    int getTurn();
    void incrXCount(int amount = 1);
    void incrOCount(int amount = 1);
    void incrTieCount(int amount = 1);
    void setValue(int x, int y, int value);
    void setTurn(int newTurn);

    bool first;
protected:
    int investigateSlot(int x, int y, int dX, int dY, int piece);

    static long long unsigned int xCount;
    static long long unsigned int oCount;
    static long long unsigned int tieCount;
    int turn; //Whose turn it is RIGHT NOW. As in, ON THIS NODE!

    static long long unsigned int count;

    #ifdef SDL_ENABLED
        SDL_Thread* threads[GRID_X * GRID_Y]; //One thread per open slot.
    #endif // SDL_ENABLED

    int board[GRID_X][GRID_Y];
};
int exploreNode(void* data);
