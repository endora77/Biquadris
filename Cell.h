#ifndef BIQUADRIS_CELL_H
#define BIQUADRIS_CELL_H
#include "Subject.h"
#include "Block.h"
#include <utility>

class Cell: public Subject{
    // Given the position of the cell on the board
    std::pair<int, int> position;
    BlockType type;

public:
    // Constructor
    Cell(int row, int column, BlockType type, Block* block);

    void setPosition(const int row, const int col){
        position.first = row;
        position.second = col;
        notifyObservers();
    }
    // moveDown(int num) moves the cell "num" cell down
    void moveDown(int num);
    // moveLeft(int num) moves the cell "num" cell left
    void moveLeft(int num);
    // moveRight(int num) moves the cell "num" cell right
    void moveRight(int num);

    // getState() returns the status of the cell (filled or not)
    int getState() const override;
    // getPosition() returns the position of the cell on the board
    std::pair<int, int> getPosition() const;

    BlockType getType() const{
        return type;
    }

};


#endif //BIQUADRIS_CELL_H
