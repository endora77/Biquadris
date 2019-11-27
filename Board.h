#ifndef BOARD_H
#define BOARD_H
#include "Observer.h"
#include "Cell.h"
#include <vector>
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
    TextDisplay textdisplay;
    
    const int gridH;
    const int gridW;
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::unique_ptr<Block>> blocks;

    int countBlocks;
    int totalScore;
    int tempScore;
    BlockType nextType;
    
public:
    Block* currentBlock;
    Board(const int height, const int width, const vector<Display>* displays, const string* fileName):
        gridH{height}, gridW{width}, countBlocks{0}, totalScore{0}, tempScore{0}{
        level = new LevelZero{};
        nextType = level->nextType();
        restriction->reset(new Restriction{false, BlockType::LBlock, false, false});
        blockFile.open(fileName->c_str());
    }
 
    ~Board(){
        delete level;
        delete currentBlock;
        blockFile.close();
        for(auto &b : blocks) delete(b);
    }

//return the row number of the first cell that is empty in this column
    void newBlock(const BlockType type, const int row, const int col);
    int checkColBot(int col);
    bool checkPosition(const unique_ptr<pair<int, int>[]>& pos) const;
    void checkFilledLines();
    void addStar();
    void deleteRow(int row);
    bool checkTop();
    void notify(Subject* s);
    void draw();
};

#endif