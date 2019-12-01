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
    
public:
    friend class Player;
    friend class TextDisplay;
    Block* currentBlock;

    Board(const int height = 15, const int width = 11):
    gridH{height + 3}, gridW{width}, countBlocks{0}, totalScore{0}, tempScore{0},numDeleted{0}{
        std::vector<Cell*> temp(gridW, nullptr);
        for(int i  = 0; i < gridH; i++)grid.emplace_back(temp);
    }

    Block* newBlock(const BlockType type, const int row, const int col, const int level);
    int checkColBot(int col);
    bool checkPosition(Block* checkBlock, const std::unique_ptr<std::pair<int, int>[]>& pos);
    void checkFilledLines(const Level* level);
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
