#ifndef BOARD_H
#define BOARD_H
#include "Observer.h"
#include "Cell.h"
#include <vector>
//#include "Restriction.h"
//#include "Level.h"
class Board: public Observer{
    const int gridH;
    const int gridW;
    std::vector<std::vector<Cell*>> grid;
    int countBlocks;
    std::vector<Block*> blocks;
    Block* currentBlock;
    Level* level;
    int totalScore;
    int tempScore;
    BlockType nextType;
    *Restriction restriction;

    void newBlock(const BlockType type, const int row, const int col);
    bool checkPosition(const std::pair<int, int> *pos) const;
    void drop(const int i);
//return the row number of the first cell that is empty in this column
    int checkColBot(int col);
    void checkFilledLines();
    void addStar();
    void deleteRow(int row);
    bool checkTop();
    void notify(Subject* s);

public:
    void setLevel(int l);
    void getNextBlock();
    void down(const int i);
    void left(const int i);
    void right(const int i);
    void rotateClockwise(const int i);
    void rotateCounterClockwise(const int i);

};






#endif