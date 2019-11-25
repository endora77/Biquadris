#include "Block.h"
#include "Enums.h"
#include <utility>

// calcPosition(MoveType type, int num) returns the pointer to the position of the first cell
std::unique_ptr<std::pair<int, int>[]> Block::calcPosition(const MoveType type){
    std::unique_ptr<std::pair<int, int>[]> calculates(new std::pair<int, int>[numCells]);
    int i = 0;
    for (auto it = cells.begin(); it != cells.end(); it++){
        calculates[i] = it->getPosition();
        i++;
    }
    switch(type){
        case MoveType::moveDown: {
            for (int i = 0; i < numCells; i++){
                calculates[i].first ++;
            }
            break;
        }
        case MoveType::moveLeft: {
            for (int i = 0; i < numCells; i++){
                calculates[i].second --;
            }
            break;
        }
        case MoveType::moveRight: {
            for (int i = 0; i < numCells; i++){
                calculates[i].second ++;
            }
            break;
        }
        case MoveType::moveClockwise: {
            Clockwise(calculates, numCells);
            break;
        }
        default:{
            counterClockwise(calculates, numCells);
        }
    }
    return calculates;
}

void Block::Clockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num){
    int row, col, negWidth;
    getPos(poses, num, row, col, negWidth);
    for (int i = 0; i < num; i++){
        int hDif = poses[i].first - row;//negative
        int wDif = poses[i].second - col;//positive
        poses[i].first = col + negWidth - wDif;
        poses[i].second = col + hDif;
    }
}

void Block::counterClockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num){
    Clockwise(poses, num);
    Clockwise(poses, num);
    Clockwise(poses, num);
}

void Block::getPos(std::unique_ptr<std::pair<int, int>[]>& poses, const int num, int& row, int& col, int&negWidth){
    row = INT16_MAX;
    col = INT16_MIN;
    int right = INT16_MAX;
    for (int i = 0; i < num; i++){
        if(poses[i].first > row)row = poses[i].first;
        if(poses[i].second < col)col = poses[i].second;
        if(poses[i].second > right)right = poses[i].second;
    }
    negWidth = col - right;
}

//Finished Below********************************************************************************************
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

void Block::Clockwise(){
    int row, col, negWidth;
    getPos(cells, row, col, negWidth);
    for (auto& c: cells){
        std::pair<int, int> temp = c.getPosition();
        int hDif = temp.first - row;//negative
        int wDif = temp.second - col;//positive
        c.setPosition(col + negWidth - wDif, col + hDif);
    }
}

void Block::getPos(std::vector<Cell> &cells, int& row, int& col, int&negWidth){
    row = INT16_MAX;
    col = INT16_MIN;
    int right = INT16_MAX;
    for (auto& c: cells){
        std::pair<int, int> temp = c.getPosition();
        if(temp.first > row)row = temp.first;
        if(temp.second < col)col = temp.second;
        if(temp.second > right)right = temp.second;
    }
    negWidth = col - right;
}

void Block::counterClockwise(){
    Clockwise();
    Clockwise();
    Clockwise();
}

Block::~Block(){}

Block::Block(const int level, const int numCells, Observer* obs): 
    level{level}, numCells{numCells}{
    deleted = false;
    attach(obs);
}