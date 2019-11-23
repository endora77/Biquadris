#include "Cell.h"
#include "Enums.h"
#include <utility>

using namespace std;

// Constructor
Cell::Cell(bool filled, int row, int column, BlockType type) {
    this->filled = filled;
    position = make_pair(row, column);
    this->type = type;
}

// setPosition(int row, int column) modifies the Cell's position of the board
// This method would only be called to handle rotation (i.e. clockwise and counterclockwise)
void Cell::setPosition(int row, int column) {
    position.first = row;
    position.second =
}

// notifyObservers() notifies the Block that the cell belongs to when changing position
void Cell::notifyObservers() {

}

// getPosition() returns the reference to the position of the cell on the board
std::pair<int, int> &Cell::getPosition() {
    return *position;
}


// getState() returns the status of the cell (filled or not)
bool Cell::getState() {
    return filled;
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