#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include "block.h"
#include <string>

class Player{
    std::string name;
    bool isSpecialHeavy;
    bool isForce;
    bool isBlind;
public:
    Board *board;
    void forceOther(Player *p, BlockType bType);
    void heavyOther(Player *p);
    void blindOther(Player *p);
    int getScore();
    std::string getName();
    void reset();
    void left
};
