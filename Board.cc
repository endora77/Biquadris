#include "Board.h"
#include <iostream>
using namespace std;


void Board::checkFilledLines(const Level* level){
    tempScore = 0;;
    numDeleted  = 0;
    for(int i = gridH - 1; i > 3; i--){
        bool filled = true;
        bool emptyLine = true;
        for(int j = 0; j < gridW; j++){
            if(grid[i][j]) emptyLine = false;
            if(!grid[i][j]) filled = false;
        }
        if(emptyLine) break;
        if(filled) {
            numDeleted ++;
            deleteRow(i);
        }
    }
    if(!numDeleted) countBlocks ++;
    else countBlocks = 0;
    if(5 == countBlocks){
        if(level->addStar()) addStar();
        countBlocks = 0;
    }
    tempScore += numDeleted;
    totalScore += tempScore*tempScore;
}

bool Board::checkPosition(Block* checkBlock, const unique_ptr<pair<int, int>[]>& pos){
    eraseBlock(checkBlock);
    for( int i = 0; i < 4; i++){
        if(grid[pos[i].first][pos[i].second]){
            addBlock(checkBlock);
            return false;
        }
    }
    addBlock(checkBlock);
    return true;
}

//return the row number of the first cell that is empty in this column
int Board::checkColBot(int col){
    if(col < gridW){
        int i = gridH - 1;
        while(i >= 0 && grid[i][col] != nullptr) i --;
        return i;
    }
    return -1;
}
bool Board::checkTop(){
    for(int i = 0; i < gridW; i++){
        if(grid[3][i]) return true;
    }
    return false;
}

void Board::deleteRow(int row){
    for(int i = 0; i < gridW; i++){
        grid[row][i]->setPosition(-1, -1);
        grid[row][i]->notifyObservers();
    }
}

void Board::addStar(){
    int mid = gridW/2;
    int lowest = checkColBot(mid);
    std::unique_ptr<Block> b = make_unique<StarBlock>(StarBlock{0, mid, 0, this});
    blocks.push_back(std::move(b));
    grid[lowest][mid] = &(b->getCells()[0]);
}

Block* Board::newBlock(const BlockType type, const int row, const int col, const int level){
    switch(type){
        case BlockType::ZBlock: {
            blocks.emplace_back(make_unique<ZBlock>(row, col, level, this));break;
        }
        case BlockType::LBlock:{
            blocks.emplace_back(make_unique<LBlock>(row, col, level, this));break;
        }
        case BlockType::IBlock: {
            blocks.emplace_back(make_unique<IBlock>(row, col, level, this)); break;
        }
        case BlockType::JBlock: {
            blocks.emplace_back(make_unique<JBlock>(row, col, level, this));break;
        }
        case BlockType::OBlock:{
            blocks.emplace_back(make_unique<OBlock>(row, col, level, this));break;
        }
        case BlockType::SBlock: {
            blocks.emplace_back(make_unique<SBlock>(row, col, level, this));break;
        }
        case BlockType::TBlock: {
            blocks.emplace_back(make_unique<TBlock>(row, col, level, this));break;
        }
        case BlockType::StarBlock: {
            blocks.emplace_back(make_unique<StarBlock>(row, col, level, this));break;
        }
    }
    currentBlock = blocks.back().get();
    numDeleted = 0;
    return currentBlock;
}

void Board::restart(){
    currentBlock = nullptr;
    blocks.clear();
    for(auto &a : grid){
        for(auto &b: a){
            b = nullptr;
        }
    }
    countBlocks = 0;
    totalScore = 0;
    tempScore = 0;
}

void Board::eraseBlock(Block* block){
    const vector<Cell>& cells = block->getCells();
    for(auto& c : cells){
        pair<int, int> pos = c.getPosition();
        grid[pos.first][pos.second] = nullptr;
    }
}

void Board::addBlock(Block* block){
    vector<Cell>& cells = block->getCells();
    for(auto& c : cells){
        pair<int, int> pos = c.getPosition();
        grid[pos.first][pos.second] = &c;
    }
}
