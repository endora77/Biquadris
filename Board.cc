#include "Board.h"
using namespace std;
//Throws an error
void Board::setLevel(int l){
    delete level;
    switch(l){
        case 0:{
            level = new LevelZero(); break;
        }
        case 1:{
            level = new LevelOne(); break;
        }
        case 2:{
            level = new LevelTwo(); break;
        }
        case 3:{
            level = new LevelThree(); break;
        }
        case 4:{
            level = new LevelFour(); break;
        }
        default: throw "Invalid level";
    }
    nextType = level->nextBlock();
}

void Board::newBlock(const BlockType type, const int row, const int col){
    switch(type):{
        case typeZ: return new ZBlock{row, col, level};
        ...
        //Not finished, and every other blocks
    }
}

void Board::getNextBlock(){
    tempScore = 0;
    BlockType type;
    if(restriction->forced()) type = restriction->getForcedType();
    else type = nextType;
    currentBlock = newBlock{type, 0, 3};
    blocks.push_back(currentBlock);
}

bool Board::checkPosition(const std::pair<int, int> *pos) const{
    for( int i = 0; i < 4; i++){
        if(cells[pos[i].first][pos[i].second]) return false;
    }
    return true;
}

void Board::down(const int i){
    //Not finished, should use unique pointer here or vector
    pair<int, int> *pos = currentBlock->calcPosition(MoveType::moveDown, i);
    if(Board::checkPosition(pos)) level->down(*currentBlock, i);
}

void Board::left(const int i){
    pair<int, int> *pos = currentBlock->calcPosition(MoveType::moveLeft, i);
    if(Board::checkPosition(pos)) currentBlock->left(i);
}

void Board::right(const int i){
    pair<int, int> *pos = currentBlock->calcPosition(MoveType::moveRight, i);
    if(Board::checkPosition(pos)) currentBlock->right(i);
}

void Board::rotateClockwise(const int i){
    pair<int, int> *pos = currentBlock->calcPosition(MoveType::moveClockwise, i);
    if(Board::checkPosition(pos)) 
        currentBlock = new Clockwise{*currentBlock};
}

void Board::rotateCounterClockwise(const int i){
    pair<int, int> *pos = currentBlock->calcPosition(MoveType::moveCounterClockwise, i);
    if(Board::checkPosition(pos))
     currentBlock = new rotateCounterClockwise{*currentBlock};
}

//return the row number of the first cell that is empty in this column
int Board::checkColBot(int col){
    if(col < gridW){
        int i = gridH - 1;
        while(i >= 0 && grid[i][col] != nullptr) i --;
        return i;
    }
    throw "In checkColBot(): col number out of range";
}

void Board::drop(){
    vector<Cell>& c = currentBlock->getCells();
    int lowest = gridH;
    int touchedCell = 0;
    for(int i = 0; i < 4; i++){
        pair<int, int> pos = c[i].getPosition();
        int temp = checkColBot(pos.second);
        if(temp < lowest){
            touchedCell = i;
            lowest = temp;
        } 
    }
    int shift = lowest - c[i].getPosition().first;
    currentBlock->down(shift);
}


void Board::checkFilledLines(){
    int numDeleted  = 0;
    for(int i = gridH - 1; i > 3; i++){
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
        if(level->addStar) addStar();
        countBlocks = 0;
    }
    tempScore += numDeleted;
    totalScore += tempScore*tempScore;
    tempScore = 0;
}

void Board::addStar(){
    int mid = gridW/2;
    int lowest = checkColBot(mid);
    Block* star = new starBlock{};
    blocks.push_back(star);
    grid[lowest][mid] = star;
}

void Board::deleteRow(int row){
    for(int i = 0; i < gridW; i++){
        grid[row][i]->setPosition(-1, -1);
        grid[row][i]->notifyObservers();
    }
}

bool Board::checkTop(){
    for(int i = 0; i < gridW; i++){
        if(grid[3][i]) return true;
    }
    return false;
}

void Board::notify(Subject* s){
    tempScore += s->getState();
    for(auto a = blocks.begin(); a != blocks.end(); )
}