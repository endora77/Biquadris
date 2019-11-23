#ifndef BIQUADRIS_BLOCK_H
#define BIQUADRIS_BLOCK_H

class Cell;

class Block {
    // Check if the Block is deleted
    bool deleted;
    // "level" tracks the the level number when the Block is created
    int level;
    // getCells() returns an array of Cell pointers where the cells are filled
    Cell *[4] getCells() = 0;

public:
    void notify();
    // checkExist() returns the boolean value of whether the Block exists on the Board
    bool checkExist();
    // getLevel() returns the level of the the Block when it's been created
    int getLevel();
    // calcPosition(MoveType type, int num) returns the position of the
    std::pair<int, int> *calcPosition(Movetype type, int num);
    // down(int num) moves the position of the Block down "num" cell(s)
    void down(int num);
    // left(int num) moves the position of the Block left "num" cell(s)
    void left(int num);
    // right(int num) moves the position of the Block right "num" cell(s)
    void right(int num);
};


#endif //BIQUADRIS_BLOCK_H
