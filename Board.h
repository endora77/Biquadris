#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <fstream>

//Safe to include block.h, blocks would notify the board.
#include "Block.h"
#include "BlockFiles/ZBlock.h"
#include "BlockFiles/LBlock.h"
#include "BlockFiles/IBlock.h"
#include "BlockFiles/JBlock.h"
#include "BlockFiles/OBlock.h"
#include "BlockFiles/SBlock.h"
#include "BlockFiles/TBlock.h"
#include "BlockFiles/StarBlock.h"

//Safe to include
#include "Observer.h"
#include "Enums.h"
#include "Level.h"
//Not safe to include, since Board includes Display, Display includes Game, Game inlcudes player, Player includes Board

class Board final: public Observer{
    const int gridH;
    const int gridW;
    
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::unique_ptr<Block>> blocks;

    int countBlocks;
    int numDeleted;
    int totalScore;
    int tempScore;
    std::unique_ptr<Level>& level;
    
public:
    friend class Player;
    friend class TextDisplay;
    Block* currentBlock;

    Board(std::unique_ptr<Level>& level, const int height = 15, const int width = 11):
        gridH{height}, gridW{width}, countBlocks{0}, totalScore{0}, tempScore{0}, level{level}{
        std::vector<Cell*> temp(gridW, nullptr);
        for(int i  = 0; i < gridH; i++)grid.emplace_back(temp);
    }

    Block* newBlock(const BlockType type, const int row, const int col);
    int checkColBot(int col);
    bool checkPosition(const std::unique_ptr<std::pair<int, int>[]>& pos) const;
    void checkFilledLines();
    void addStar();
    void deleteRow(int row);
    bool checkTop();

    void draw();
    void restart();
    void eraseBlock(Block* block);
    void addBlock(Block* block);
    int getLinesDeleted(){
        return numDeleted;
    }
    //Add score when a block is deleted:
    void notify(Subject* s)override{
        tempScore += s->getState();
    }
};

#endif
