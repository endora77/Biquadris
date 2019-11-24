#ifndef BIQUADRIS_BLOCK_H
#define BIQUADRIS_BLOCK_H
#include <utility>
#include <memory>
#include <vector>
#include "Enums.h"
#include "Observer.h"
class Cell;

class Block: public Observer, public Subject{
    // Check if the Block is deleted
    bool deleted;
    // "level" tracks the the level number when the Block is created
    int level;
protected:
    std::vector<Cell> cells;
    const int numCells;
    // // getCells() returns an array of Cell pointers where the cells are filled
    // Cell *[4] getCells() = 0;

public:
    Block(const int level, const int numCells, Observer* obs): level{level}, numCells{numCells}{
        deleted = false;
        attach(obs);
    }
    void notify() override;
    // checkExist() returns the boolean value of whether the Block exists on the Board
    bool checkExist();
    // getLevel() returns the level of the the Block when it's been created
    int getLevel();
    // calcPosition(MoveType type, int num) returns the position of the
    std::pair<int, int> *calcPosition(const MoveType type, const int num) const;
    // down(int num) moves the position of the Block down "num" cell(s)
    void down(int num);
    // left(int num) moves the position of the Block left "num" cell(s)
    void left(int num);
    // right(int num) moves the position of the Block right "num" cell(s)
    void right(int num);
    
    virtual std::vector<Cell>& getCells() = 0;
};


#endif //BIQUADRIS_BLOCK_H
