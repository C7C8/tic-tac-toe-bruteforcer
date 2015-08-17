#include "Node.h"

//#define SDL_ENABLED

#ifdef SDL_ENABLED
    SDL_SpinLock outputLock = 0;
#endif // SDL_ENABLED

long long unsigned int Node::count = 0;
long long unsigned int Node::oCount = 0;
long long unsigned int Node::xCount = 0;
long long unsigned int Node::tieCount = 0;

/** @brief Increments the tie count.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrTieCount(int amount)
{
    tieCount += amount;
}

/** @brief Increments the O win count.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrOCount(int amount)
{
    oCount += amount;
}

/** @brief Increments the X win count.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrXCount(int amount)
{
    xCount += amount;
}

/** @brief Gets the tie count
  */
int Node::getTieCount() const
{
    return tieCount;
}

/** @brief Gets the O win count.
  */
int Node::getOCount() const
{
    return oCount;
}

/** @brief Gets the X win count.
  */
int Node::getXCount() const
{
    return xCount;
}

/** @brief Gets what type of ending this board contains. Complexity increases with board size and fill level of board.
  * @return Enumerated end type
  */
endType Node::getEndType(int winDist)
{
    //Universal win detector. Works by detecting straight lines.
    for (int iX = 0; iX < GRID_X; ++iX)
    {
        for (int iY = 0; iY < GRID_Y; ++iY)
        {
            //Check for empty space
            if (board[iX][iY] == 0)
                continue;

            int piece = board[iX][iY]; //What piece is at this spot?
            //Begin line identification process. i and j are the directions to move in.
            for (int i = -1; i < 2; ++i)
            {
                for (int j = -1; j < 2; ++j)
                {
                    if (i == 0 && j == 0)
                        continue; //Skip spots of not moving at all.

                    int lineLength = investigateSlot(iX, iY, i, j, piece) + 1; //+1 to account for THIS spot.
                    if (lineLength < winDist)
                        continue;

                    if (piece == PIECE_X)
                        return XWIN; //Unrelated to XBOX.
                    else if (piece ==PIECE_O)
                        return OWIN;
                }
            }
        }
    }

    //Check for tie condition (last step)
    bool tie = true;
    for (int iX = 0; iX < GRID_X; ++iX)
    {
        for (int iY = 0; iY < GRID_Y; iY++)
        {
            if (board[iX][iY] == 0)
                tie = false;
        }
    }
    if (tie)
        return TIE;
    else
        return NONE;
}

/** @brief Solves for all of this node's children.
  */
void Node::solveForChildren()
{
    #ifdef SDL_ENABLED
        int threadcount = 0;
    #endif // SDL_ENABLED

    for (int iX = 0; iX < GRID_X; ++iX)
    {
        for (int iY = 0; iY < GRID_Y; ++iY)
        {
            //Check if this spot is already occupied.
            if (board[iX][iY] != 0)
                continue;

            Node newNode;
            newNode.turn = turn * -1;
            newNode.first = false; //Just in case?

            //Copy this node's board over to the child node
            for (int jX = 0; jX < GRID_X; ++jX)
                for (int jY = 0; jY < GRID_Y; ++jY)
                    newNode.board[jX][jY] = board[jX][jY];

            //Apply the possible move.
            newNode.board[iX][iY] = newNode.turn;

            //Check this new node.
            endType nodeType = newNode.getEndType();
            if (nodeType == XWIN)
                newNode.incrXCount();
            else if (nodeType == OWIN)
                newNode.incrOCount();
            else if (nodeType == TIE)
                newNode.incrTieCount();
            else
            {
                #ifdef SDL_ENABLED
                    if (!first)
                    {
                        newNode.solveForChildren();
                        continue;
                    }
                    else
                    {
                        threads[threadcount] = SDL_CreateThread(exploreNode, "explorer thread", (void*)&newNode);
                        cout << "Creating thread #" << threadcount << " with ID " << SDL_GetThreadID(threads[threadcount]) << endl;
                        threadcount++;
                    }

                #else
                    newNode.solveForChildren();
                    continue;
                #endif //SDL_ENABLED
            }
        }
    }
    #ifdef SDL_ENABLED
        //Wait for all threads to complete if there are any...
        if (first)
            for (int i = 0; i < GRID_X * GRID_Y; ++i)
            {
                cout << "Waiting on thread #" << i << " with ID " << SDL_GetThreadID(threads[i]) << endl;
                SDL_WaitThread(threads[i], nullptr);
            }

    #endif // SDL_ENABLED
}

/** @brief Returns the total count of all the node objects that have ever been created here.
  */
int Node::getCount()
{
    return count;
}

/** @brief Sets all values up, increments the global object count.
  */
Node::Node()
{
    turn = PIECE_O; //This is so the first move registered is X if solveForChildren() is called.
    first = false;

    count++;
    if (count % 1000000 == 0)
    {
        #ifdef SDL_ENABLED
            SDL_AtomicLock(&outputLock);
            cout << "Count: " << count << endl;
            SDL_AtomicUnlock(&outputLock);
        #else
            cout << "Count: " << count << endl;
        #endif
    }

    //Initialize board
    for (int x = 0; x < GRID_X; ++x)
        for (int y = 0; y < GRID_Y; ++y)
            board[x][y] = 0;
}

/** @brief Recursively finds the longest line given a starting spot, a direction, and a piece to look for.
  * @return The maximum line length found.
  */
int Node::investigateSlot(int x, int y, int dX, int dY, int piece)
{
    int iX = x + dX;
    int iY = y + dY;

    //Out-of-bounds checking
    if (iX < 0 || iX >= GRID_X)
        return 0;
    if (iY < 0 || iY >= GRID_Y)
        return 0;

    //Perform actual check for the selected piece on this location
    if (board[iX][iY] != piece)
        return 0;
    return investigateSlot(iX, iY, dX, dY, piece) + 1; //Return a plus 1 to indicate that yes, this was another segment in the line.
}

int Node::getValue(int x, int y)
{
    if (x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y)
        return board[x][y];
    return -2; //Not a real value - indicates error condition.
}
int Node::getTurn()
{
    return turn;
}
void Node::setValue(int x, int y, int value)
{
    if (x >= 0 && x < GRID_X && y >= 0 && y < GRID_Y)
        board[x][y] = value;
}
void Node::setTurn(int newTurn)
{
    turn = newTurn;
}

int exploreNode(void* data)
{
    //Dumb threaded function for exploring a node... using THREADS!
    ((Node*)(data))->solveForChildren();
    return 0;
}
