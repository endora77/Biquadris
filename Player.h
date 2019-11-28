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
#include "Subject.h"
#include <string>
//Notify observers are all calle din the Game class
class Player: public Subject{
    std::string name;
   
    std::unique_ptr<Level> level;
    int currentLevel;
    int seed;
    Block* currentBlock;
    bool success;

public:
    Restriction restriction;
    BlockType forcedType;
    std::unique_ptr<Board> board;
    Player::Player(std::string name, const int level, std::vector<Display*>& displays, 
        const int height = 15, const int width = 11, int seed = 0, std::string* file_name = nullptr): 
        name{name}{
            for(auto& a : displays){
                attach(a);
            }
            setLevel(level, seed);
            currentLevel = level;
            board = std::make_unique<Board>(this->level, displays, file_name, height, width);
            this->seed = seed;
            success = true;
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
    void levelUp(){
        if(currentLevel < 4){
            currentLevel++;
            setLevel(currentLevel, seed);
        }else throw "Cannot levelup anymore.";
    }
    void levelDown(){
        if(currentLevel > 0){
            currentLevel--;
            setLevel(currentLevel, seed);
        }else throw "Cannot leveldown anymore.";
    }
    int getState()const override{
        return success;
    }
    int getLinesDeleted(){
        return board->getLinesDeleted();
    }
};

#endif