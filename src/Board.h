#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>

//Safe to include block.h, blocks would notify the board.
#include "Block.h"
#include "ZBlock.h"
#include "LBlock.h"
#include "IBlock.h"
#include "JBlock.h"
#include "OBlock.h"
#include "SBlock.h"
#include "TBlock.h"
#include "StarBlock.h"
#include "iostream"
#include "Observer.h"
#include "Enums.h"
#include "Level.h"

class Board final: public Observer{
    const int gridH;
    const int gridW;
    
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::unique_ptr<Block>> blocks;

    int countBlocks;
    int numDeleted;
    int totalScore;
    
private:
    //Check the lowest cell in this column
    int checkColBot(int col);
    
    //Check if the positon is valid for the target block
    bool checkPosition(Block* checkBlock, const std::unique_ptr<std::pair<int, int>[]>& pos);
    
    //Check which lines are filled
    void checkFilledLines(const Level* level);
    
    //Add star to the middle if neccesary
    void addStar();
    
    //Delete the row
    void deleteRow(int row);
    
    //Check if the cells have touched the top row
    bool checkTop();
    
public:
    friend class Player;
    friend class TextDisplay;
    Block* currentBlock;
    
    //Constructor
    Board(const int height = 15, const int width = 11);

    //Get the pointer to a new block
    Block* newBlock(const BlockType type, const int row, const int col, const int level);
    
    //Reset the board
    void restart();
    
    //Erase or add a block to the board
    void eraseBlock(Block* block);
    void addBlock(Block* block);
    
    //Get the number of lines that are delteted this time
    int getLinesDeleted()const;
    
    //Add score when a block is deleted:
    void notify(Subject* s)override;
};

#endif
