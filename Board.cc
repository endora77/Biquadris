#include "Board.h"
using namespace std;

bool Board::checkPosition(const unique_ptr<pair<int, int>[]>& pos) const{
    for( int i = 0; i < 4; i++){
        if(grid[pos[i].first][pos[i].second]) return false;
    }
    return true;
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
        if(level->addStar()) addStar();
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
}


