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

/** @brief Gets what type of ending this board contains.
  * @return Enumerated end type
  */
endType Node::getEndType() const
{
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
            newNode.board[iX][iY] = turn;

            //Check this new node.
            endType nodeType = newNode.getEndType();
            if (nodeType == XWIN)
                newNode.incrXCount();
            else if (nodeType == OWIN)
                newNode.incrOCount();
            else
                newNode.solveForChildren();

            cout << "Added node to end of child list. ";
            children.push_back(newNode);
            cout << "List is now of length " << children.size() << endl;
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
    turn = X;
    parent = nullptr;
    count++;

    //Initialize board
    for (uint8_t x = 0; x < GRID_X; ++x)
        for (uint8_t y = 0; y < GRID_Y; ++y)
            board[x][y] = 0;
}

