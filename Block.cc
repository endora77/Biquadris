#include "Block.h"
#include "Enums.h"
#include <utility>

// calcPosition(MoveType type, int num) returns the pointer to the position of the first cell
// after perform the move
std::pair<int, int> *Block::calcPosition(const MoveType type) const{
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

// down(int num) moves the position of the Block down
void Block::down() {
    for (auto& c: cells) c.moveDown();
}

// left(int num) moves the position of the Block left
void Block::left() {
    for (auto& c: cells) c.moveLeft();
}
// right(int num) moves the position of the Block right
void Block::right() {
    for (auto& c: cells) c.moveRight();
}

std::vector<Cell>& Block::getCells(){
    return cells;
}

Block::~Block(){}