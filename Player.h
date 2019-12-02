#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "LevelZero.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include "Level.h"
#include "Subject.h"
#include "Board.h"


//Notify observers are all called in the Game class
class Player final: public Subject{
    std::string name;
    //Sequnce file for level0
    std::string file0;
    //Current level
    std::unique_ptr<Level> level;
    int currentLevel;
    //Seed for levels that are using random sequnces
    int seed;
    //Pointer to the current undropped block
    Block* currentBlock;
    //Records if the player has lost
    bool success;
    
public:
    //The next block type
    BlockType nextType;
    //If any special effects is active
    Restriction restriction;
    //If forced, the forced type
    BlockType forcedType;
    //Whether or not the player is playing
    bool playing;
    //The board that stores all the blocks' information
    std::unique_ptr<Board> board;
    
private:
    //Calculate how many downs are needed
    void getHorizontalDowns(std::unique_ptr<std::pair<int, int>[]>& pos, int& downs, const int blockSize);
public:
    //Constructor
    Player(std::string name, const int lev, std::vector<std::unique_ptr<Observer>>& displays,
           const int height = 15, const int width = 11, int seed = 0, const std::string file0 = "no_file_specified");
    
    //Change level functions
    void setLevel(const int l, unsigned int seed);
    void levelUp();
    void levelDown();

    //Movement functions
    void down(const int times);
    void left(const int times);
    void right(const int times);
    void rotateClockwise(const int times);
    void rotateCounterClockwise(const int times);
    void drop();
    
    //Get player information functions
    std::string getName()const;
    int getScore() const;
    int getState()const override;
    int getLinesDeleted()const;
    
    //Clear any restrictions for next round
    void resetRestrictions();
    //Restart the game and clear the player's board
    void restart();
    //Get a new block
    bool getNextBlock();
    //Turn off and on the randomness of the blocks
    bool norand(const std::string file);
    bool rand();
    //Set the current block to the required type
    bool setBlock(BlockType type);
    friend class TextDisplay;
};

#endif
