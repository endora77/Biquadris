#ifndef BOARD_H
#define BOARD_H
#include "Observer.h"
#include "Cell.h"
#include <vector>
#include "TextDisplay.h"
#include "Enums.h"
#include <string>
#include <fstream>
struct Restriction{
    const bool forced;
    const BlockType forcedType;
    const bool specialHeavy;
    const bool blind;
};

class Board: public Observer{
    std::ifstream blockFile;
    TextDisplay textdisplay;
    
    const int gridH;
    const int gridW;
    std::vector<std::vector<Cell*>> grid;
    int countBlocks;
    std::vector<Block*> blocks;
    Block* currentBlock;
    int totalScore;
    int tempScore;
    BlockType nextType;

    bool checkPosition(const unique_ptr<pair<int, int>[]>& pos) const;
    
//return the row number of the first cell that is empty in this column
    int checkColBot(int col);
    void checkFilledLines();
    void addStar();
    void deleteRow(int row);
    bool checkTop();
    void notify(Subject* s);
    void draw();
    
public:

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
};






#endif