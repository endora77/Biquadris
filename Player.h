#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "block.h"
#include "Enums.h"
#include "LevelZero.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include <string>
class Player{
    std::string name;
    BlockType forcedType;
    bool specialHeavy;
    bool forced;
    bool blind;
    std::unique_ptr<Level> level;
    Block* currentBlock;
public:
    Board *board;

    std::string getName()const;
    void reset();
    int getScore() const;

    void setLevel(const int l, int seed);
    void getNextBlock();
    void down();
    void left();
    void right();
    void rotateClockwise();
    void rotateCounterClockwise();
    void drop();

    // void forceOther(Player *p, BlockType bType);
    // void heavyOther(Player *p);
    // void blindOther(Player *p);
};

#endif