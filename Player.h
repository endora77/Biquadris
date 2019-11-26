#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "block.h"
#include "BlockFiles/ZBlock.h"
#include "BlockFiles/LBlock.h"
#include "BlockFiles/IBlock.h"
#include "BlockFiles/JBlock.h"
#include "BlockFiles/OBlock.h"
#include "BlockFiles/SBlock.h"
#include "BlockFiles/TBlock.h"
#include "BlockFiles/StarBlock.h"
#include "Level.h"
#include <string>
struct Restriction{
    const bool forced;
    const BlockType forcedType;
    const bool specialHeavy;
    const bool blind;
};

class Player{
    std::string name;
    bool isSpecialHeavy;
    bool isForce;
    bool isBlind;
    Level* level;
public:
    Board *board;
    void forceOther(Player *p, BlockType bType);
    void heavyOther(Player *p);
    void blindOther(Player *p);
    int getScore();
    std::string getName();
    void reset();

    void newBlock(const BlockType type, const int row, const int col);
    void setLevel(const int l, const BlockType type, int seed);
    void getNextBlock();
    void down(const int i);
    void left(const int i);
    void right(const int i);
    void rotateClockwise(const int i);
    void rotateCounterClockwise(const int i);
    void drop();
};

