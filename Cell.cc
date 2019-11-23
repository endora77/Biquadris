#include "Cell.h"
#include "Enums.h"
#include <utility>

using namespace std;


// notifyObservers() notifies the Block that the cell belongs to when changing position
void Cell::notifyObservers() {
    
}

//Finished Below****************************************************************************************************************
// Constructor
Cell::Cell(int row, int column, BlockType type): type{type}{
    position = make_pair(row, column);
}
// getPosition() returns the reference to the position of the cell on the board
std::pair<int, int> Cell::getPosition() const{
    return position;
}

// getState() returns the status of the cell (filled or not)
bool Cell::getState() const{
    if(position.first == -1) return false;
    return true;
}

// moveDown(int num) moves the cell "num" cell down
void Cell::moveDown(int num) {
    position.first += num;
}

// moveLeft(int num) moves the cell "num" cell left
void Cell::moveLeft(int num) {
    position.second -= num;
}

// moveRight(int num) moves the cell "num" cell right
void Cell::moveRight(int num) {
    position.second += num;
}