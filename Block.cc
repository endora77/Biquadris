#include "Block.h"
#include "Enums.h"
#include <utility>

// calcPosition(MoveType type, int num) returns the pointer to the position of the first cell
// after perform the move for "num" cells
std::pair<int, int> *Block::calcPosition(const MoveType type, const int num) const{
    if (type == MoveType::moveDown) {
        return make_
    }
    if (type == MoveType::moveLeft) {}
    if (type == MoveType::moveRight) {}
    if (type == MoveType::moveClockwise) {}
    if (type == MoveType::moveCounterClockwise) {}
}

//Finished Below********************************************************************************************
//I don't know w this is wrong
void Block::notify(){
    if(!checkExist()){
        deleted = true;
        notifyObservers();
    }
}

bool Block::checkExist() {
    int i = 0;
    for(auto&c : cells){
        if(c.getState()) break;
        i++;
    }
    if (i == numCells) return false;
    else return true;
}

// getLevel() returns the level of the the Block when it's been created
int Block::getLevel() {
    return level;
}

// down(int num) moves the position of the Block down "num" cell(s)
void Block::down(int num) {
    for (auto& c: cells) c.moveDown(num);
}

// left(int num) moves the position of the Block left "num" cell(s)
void Block::left(int num) {
    for (auto& c: cells) c.moveLeft(num);
}
// right(int num) moves the position of the Block right "num" cell(s)
void Block::right(int num) {
    for (auto& c: cells) c.moveRight(num);
}

std::vector<Cell>& Block::getCells(){
    return cells;
}

Block::~Block(){}