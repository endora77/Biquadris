#include "Block.h"
#include "Enums.h"
#include "Cell.h"
#include <utility>

// calcPosition(MoveType type, int num) returns the pointer to the position of the first cell
std::unique_ptr<std::pair<int, int>[]> Block::calcPosition(const MoveType type) const{
    std::unique_ptr<std::pair<int, int>[]> calculates(new std::pair<int, int>[numCells]);
    int i = 0;
    for (auto& c: cells){
        calculates[i] = c.getPosition();
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
    return std::move(calculates);
}
void Block::furtherCalculates(const MoveType type, std::unique_ptr<std::pair<int, int>[]>& calculates, const int numCells){
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
}
void Block::Clockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num){
    int row, col, right;
    getPos(poses, num, row, col, right);
    for (int i = 0; i < num; i++){
        int hDif = row - poses[i].first;//positive
        int wDif = right - poses[i].second;//positive
        poses[i].first = row - wDif;
        poses[i].second = col + hDif;
    }
}

void Block::counterClockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num){
    Clockwise(poses, num);
    Clockwise(poses, num);
    Clockwise(poses, num);
}

void Block::getPos(std::unique_ptr<std::pair<int, int>[]>& poses, const int num, int& row, int& col, int&right){
    row = INT16_MIN;
    col = INT16_MAX;
    right = INT16_MIN;
    for (int i = 0; i < num; i++){
        if(poses[i].first > row)row = poses[i].first;
        if(poses[i].second < col)col = poses[i].second;
        if(poses[i].second > right)right = poses[i].second;
    }
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
    for(auto&a : cells){
        if(a.getState()) break;
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
    int row, col, right;
    getPos(cells, row, col, right);
    for (auto& c: cells){
        std::pair<int, int> temp = c.getPosition();
        int hDif = row - temp.first;//positive
        int wDif = right - temp.second;//positive
        c.setPosition(row - wDif, col + hDif);
    }
}

void Block::getPos(std::vector<Cell> &cells, int& row, int& col, int&right){
    row = INT16_MIN;
    col = INT16_MAX;
    right = INT16_MIN;
    for (auto& c: cells){
        std::pair<int, int> temp = c.getPosition();
        if(temp.first > row)row = temp.first;
        if(temp.second < col)col = temp.second;
        if(temp.second > right)right = temp.second;
    }
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
