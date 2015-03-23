#include "Node.h"

int Node::count = 0;

/** @brief Increments the tie count. Recursively increments the count for everything above it too.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrTieCount(int amount)
{
    tieCount += amount;
    if (parent != nullptr)
        parent->incrTieCount(amount);
}

/** @brief Increments the O win count. Recursively increments the count for everything above it too.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrOCount(int amount)
{
    oCount += amount;
    if (parent != nullptr)
        parent->incrOCount();
}

/** @brief Increments the X win count. Recursively increments the count for everything above it too.
  * @param amount The amount to increment by. Can be negative.
  */
void Node::incrXCount(int amount)
{
    xCount += amount;
    if (parent != nullptr)
        parent->incrXCount();
}

/** @brief Gets the tie count
  */
uint8_t Node::getTieCount() const
{
    return tieCount;
}

/** @brief Gets the O win count.
  */
uint8_t Node::getOCount() const
{
    return oCount;
}

/** @brief Gets the X win count.
  */
uint8_t Node::getXCount() const
{
    return xCount;
}

/** @brief Gets what type of ending this board contains. Complexity increases with board size and fill level of board.
  * @return Enumerated end type
  */
endType Node::getEndType(uint8_t winDist)
{
    //Universal win detector. Works by detecting straight lines.
    for (uint8_t iX = 0; iX != GRID_X; ++iX)
    {
        for (uint8_t iY = 0; iY != GRID_Y; ++iY)
        {
            //Check for empty space
            if (board[iX][iY] == 0)
                continue;

            uint8_t piece = board[iX][iY]; //What piece is at this spot?
            //Begin line identification process. i and j are the directions to move in.
            for (uint8_t i = -1; i < 2; ++i)
            {
                for (uint8_t j = -1; j < 2; ++j)
                {
                    if (i == 0 && j == 0)
                        continue; //Skip spots of not moving at all.

                    uint8_t lineLength = investigateSlot(iX, iY, i, j, piece);
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
    for (uint8_t iX = 0; iX < GRID_X; ++iX)
    {
        for (uint8_t iY = 0; iY < GRID_Y; iY++)
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
    for (uint8_t iX = 0; iX < GRID_X; ++iX)
    {
        for (uint8_t iY = 0; iY < GRID_Y; ++iY)
        {
            //Check if this spot is already occupied.
            if (board[iX][iY] != 0)
                continue;

            Node newNode;
            newNode.parent = this;
            newNode.turn = turn * -1;

            //Copy this node's board over to the child node
            for (uint8_t jX = 0; jX < GRID_X; ++jX)
                for (uint8_t jY = 0; jY < GRID_Y; ++jY)
                    newNode.board[jX][jY] = board[jX][jY];

            //Apply the possible move.
            newNode.board[iX][iY] = newNode.turn;

            //Check this new node.
            endType nodeType = newNode.getEndType();
            if (nodeType == XWIN)
                newNode.incrXCount();
            else if (nodeType == OWIN)
                newNode.incrOCount();
            else
                newNode.solveForChildren();

            children.push_back(newNode);
        }
    }
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
    xCount = 0;
    oCount = 0;
    tieCount = 0;
    turn = PIECE_X;
    parent = nullptr;
    count++;

    //Initialize board
    for (uint8_t x = 0; x < GRID_X; ++x)
        for (uint8_t y = 0; y < GRID_Y; ++y)
            board[x][y] = 0;
}

/** @brief Recursively finds the longest line given a starting spot, a direction, and a piece to look for.
  * @return The maximum line length found.
  */
uint8_t Node::investigateSlot(uint8_t x, uint8_t y, uint8_t dX, uint8_t dY, uint8_t piece)
{
    uint8_t iX = x + dX;
    uint8_t iY = y + dY;

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
