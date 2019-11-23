#ifndef BIQUADRIS_CELL_H
#define BIQUADRIS_CELL_H

#include <utility>

class Cell {
    // Check if the cell is filled
    bool filled;
    // Given the position of the cell on the board
    std::pair<int, int> position;

public:
    // Indicate the type of Block the cell belongs to
    const BlockType type;

    // Constructor
    Cell(int row, int column, BlockType type);
    // setPosition(MoveType type, int num) modifies the position of the Cell on the board
    void setPosition(MoveType type, int num);
    // notifyObservers() notifies the Block that the cell belongs to
    void notifyObservers();
    // getPosition() returns the position of the cell on the board
    std::pair<int, int> &getPosition();
    // getState() returns the status of the cell (filled or not)
    bool getState();
    // moveDown(int num) moves the cell "num" cell down
    void moveDown(int num);
    // moveLeft(int num) moves the cell "num" cell left
    void moveLeft(int num);
    // moveRight(int num) moves the cell "num" cell right
    void moveRight(int num);

};


#endif //BIQUADRIS_CELL_H
