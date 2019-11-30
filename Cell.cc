#include "Cell.h"
#include "Enums.h"
#include <utility>

using namespace std;

// Constructor

// getPosition() returns the reference to the position of the cell on the board
std::pair<int, int> Cell::getPosition() const{
    return position;
}

// getState() returns the status of the cell (filled or not)
int Cell::getState() const{
    if(position.first == -1) return 0;
    return 1;
}

// moveDown() moves the cell down
void Cell::moveDown() {
    position.first += 1;
    notifyObservers();
}

// moveLeft() moves the cell left
void Cell::moveLeft() {
    position.second -= 1;
}

// moveRight() moves the cell right
void Cell::moveRight() {
    position.second += 1;
}

void Cell::setPosition(const int row, const int col){
    position.first = row;
    position.second = col;
}
