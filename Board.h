#ifndef BOARD_H
#define BOARD_H
#include "Observer.h"
#include "Cell.h"
#include <vector>
#include "Display.h"
#include "TextDisplay.h"
#include "Enums.h"
#include <string>
#include <fstream>
#include "BlockFiles/ZBlock.h"
#include "BlockFiles/LBlock.h"
#include "BlockFiles/IBlock.h"
#include "BlockFiles/JBlock.h"
#include "BlockFiles/OBlock.h"
#include "BlockFiles/SBlock.h"
#include "BlockFiles/TBlock.h"
#include "BlockFiles/StarBlock.h"
class Board: public Observer{
    std::ifstream blockFile;

    const int gridH;
    const int gridW;
    
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::unique_ptr<Block>> blocks;

    int countBlocks;
    int numDeleted;
    int totalScore;
    int tempScore;
    BlockType nextType;
    std::unique_ptr<Level>& level;
    
public:
    friend class Player;
    friend class TextDisplay;
    Block* currentBlock;

    Board(std::unique_ptr<Level>& level, const std::vector<Display>& displays, const int height = 15, const int width = 11,
            const string* fileName = nullptr):
        gridH{height}, gridW{width}, countBlocks{0}, totalScore{0}, tempScore{0}, level{level}{

        if(fileName) blockFile.open(fileName->c_str());
        nextType = level->nextBlock();

        //Initialize grid to null
        std::vector<Cell*> temp(gridW, nullptr);
        for(int i  = 0; i < gridH; i++)grid.emplace_back(temp);
    }
 
    ~Board(){
        delete currentBlock;
        blockFile.close();
    }

//return the row number of the first cell that is empty in this column
    Block* newBlock(const BlockType type, const int row, const int col);
    int checkColBot(int col);
    bool checkPosition(const std::unique_ptr<std::pair<int, int>[]>& pos) const;
    void checkFilledLines();
    void addStar();
    void deleteRow(int row);
    bool checkTop();
    void notify(Subject* s);
    void draw();
    void restart();
    void eraseBlock(Block* block);
    void addBlock(Block* block);
    int getLinesDeleted(){
        return numDeleted;
    }
};

#endif