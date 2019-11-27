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
#include "Display.h"
#include <string>

class Player{
    std::string name;
    BlockType forcedType;
    Restriction restriction;
    std::unique_ptr<Level> level;
    Block* currentBlock;

public:
    std::unique_ptr<Board> board;
    Player::Player(string name, const int level, std::vector<Display>& displays, 
        const int height = 15, const int width = 11, int seed = 0, std::string* file_name = nullptr): 
        name{name}{
            setLevel(level, seed);
            board = std::make_unique<Board>(this->level, displays, file_name, height, width);
        }
    
    std::string getName()const;
    void resetRestrictions();
    void restart();
    int getScore() const;

    void setLevel(const int l, int seed);
    void getNextBlock();
    void down();
    void left();
    void right();
    void rotateClockwise();
    void rotateCounterClockwise();
    void drop();

};

#endif