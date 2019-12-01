#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
//Level is safe, it does not need to know about any other class
#include "LevelZero.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include "Level.h"

//Observer, Subject, Enums are safe.
#include "Subject.h"
#include "Board.h"


//Notify observers are all calle din the Game class
class Player final: public Subject{
    std::string name;
    std::string file0;
    std::unique_ptr<Level> level;
    int currentLevel;
    int seed;
    Block* currentBlock;
    bool success;
    void getHorizontalDowns(std::unique_ptr<std::pair<int, int>[]>& pos, int& downs, const int blockSize);
public:
    BlockType nextType;
    Restriction restriction;
    BlockType forcedType;
    bool playing;
    std::unique_ptr<Board> board;
    Player(std::string name, const int lev, std::vector<std::unique_ptr<Observer>>& displays,
        const int height = 15, const int width = 11, int seed = 0, const std::string file0 = "no_file_specified"):
    name{name}, file0 {file0}, restriction{Restriction::noRestriction},playing{false}{
            for(auto& a : displays){
                attach(a.get());
            }
            setLevel(lev, seed);
            currentLevel = lev;
            board = std::make_unique<Board>(height, width);
            this->seed = seed;
            success = true;
            nextType = level->nextBlock();
        }
    
    std::string getName()const;
    void resetRestrictions();
    void restart();
    int getScore() const;

    void setLevel(const int l, unsigned int seed);
    bool getNextBlock();
    void down(const int times);
    void pureDown();
    void left(const int times);
    void right(const int times);
    void rotateClockwise(const int times);
    void rotateCounterClockwise(const int times);
    void drop();
    void levelUp();
    void levelDown();
    int getState()const override;
    int getLinesDeleted();
    bool norand(const std::string file){
       return level->unsetRandom(file);
    }
    bool rand(){
        return level->setRandom();
    }
    bool setBlock(BlockType type);
    friend class TextDisplay;
};

#endif
