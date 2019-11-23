#include "Block.h"
#include "Enums.h"
#include <utility>

void Block::notify();


// checkExist() returns the boolean value of whether the Block exists on the Board
bool Block::checkExist() {
    return exist;
}

// getLevel() returns the level of the the Block when it's been created
int Block::getLevel() {
    return level;
}

// calcPosition(MoveType type, int num) returns the pointer to the position of the first cell
// after perform the move for "num" cells
std::pair<int, int> *Block::calcPosition(MoveType type, int num) {
    if (type == MoveType::moveDown) {

    }
    if (type == MoveType::moveLeft) {}
    if (type == MoveType::moveRight) {}
    if (type == MoveType::moveClockwise) {}
    if (type == MoveType::moveCounterClockwise) {}
}


// down(int num) moves the position of the Block down "num" cell(s)
void Block::down(int num) {
    Cell *[4] cells = getCells();
    for (int i = 0; i < 4; i += 1) {
        cells[i]->moveDown(num);
    }
}

// left(int num) moves the position of the Block left "num" cell(s)
void Block::left(int num) {
    Cell *[4] cells = getCells();
    for (int i = 0; i < 4; i += 1) {
        cells[i]->moveLeft(num);
    }
}
// right(int num) moves the position of the Block right "num" cell(s)
void Block::right(int num) {
    Cells *[4] cells = getCells();
    for (int i = 0; i < 4; i += 1) {
        cells[i]->moveRight(num);
    }
}