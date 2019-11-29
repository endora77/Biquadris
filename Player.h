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
    std::string file0;
    std::unique_ptr<Level> level;
    int currentLevel;
    int seed;
    Block* currentBlock;
    bool success;
    void getHorizontalDowns(unique_ptr<pair<int, int>[]>& pos, int& downs);
public:
    Restriction restriction;
    BlockType forcedType;
    std::unique_ptr<Board> board;
    Player::Player(std::string name, const int level, std::vector<Display*>& displays, 
        const int height = 15, const int width = 11, int seed = 0, const std::string file0 = "no_file_specified"): 
        name{name}, file0 {file0}{
            for(auto& a : displays){
                attach(a);
            }
            setLevel(level, seed);
            currentLevel = level;
            board = std::make_unique<Board>(this->level, displays, height, width);
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
    void levelUp();
    void levelDown();
    int getState()const override;
    int getLinesDeleted();
    void norand(const std::string file){
       level->unsetRandom(file); 
    }
    void rand(){
        level->setRandom();
    }
};

#endif