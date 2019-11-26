#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "block.h"
#include "Enums.h"
#include "Level.h"
#include <string>
class Player{
    std::string name;
    BlockType forcedType;
    bool specialHeavy;
    bool forced;
    bool blind;
    Level* level;
public:
    Board *board;
    void forceOther(Player *p, BlockType bType);
    void heavyOther(Player *p);
    void blindOther(Player *p);
    int getScore();
    std::string getName();
    void reset();

    
    void setLevel(const int l, int seed);
    void getNextBlock();
    void down(const int i);
    void left(const int i);
    void right(const int i);
    void rotateClockwise(const int i);
    void rotateCounterClockwise(const int i);
    void drop();
};

#endif