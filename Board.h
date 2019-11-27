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
    std::unique_ptr<Level>& level;
    
public:
    Block* currentBlock;
    Board(const int height, const int width, const string* fileName, 
            const vector<Display>* displays, std::unique_ptr<Level>& level):
        gridH{height}, gridW{width}, countBlocks{0}, totalScore{0}, tempScore{0}, level{level}{
        blockFile.open(fileName->c_str());
        nextType = level->nextBlock();
    }
 
    ~Board(){
        delete currentBlock;
        blockFile.close();
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
    int getScore() const{
        return totalScore;
    }
};

#endif