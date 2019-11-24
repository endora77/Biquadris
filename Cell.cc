#include "Cell.h"
#include "Enums.h"
#include <utility>

using namespace std;

// Constructor
Cell::Cell(int row, int column, BlockType type, Block* block): type{type}{
    position = make_pair(row, column);
    this->attach(block);
}
// getPosition() returns the reference to the position of the cell on the board
std::pair<int, int> Cell::getPosition() const{
    return position;
}

// getState() returns the status of the cell (filled or not)
int Cell::getState() const{
    if(position.first == -1) return 0;
    return 1;
}

// moveDown(int num) moves the cell "num" cell down
void Cell::moveDown(int num) {
    position.first += num;
    notifyObservers();
}

// moveLeft(int num) moves the cell "num" cell left
void Cell::moveLeft(int num) {
    position.second -= num;
}

// moveRight(int num) moves the cell "num" cell right
void Cell::moveRight(int num) {
    position.second += num;
}