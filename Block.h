#ifndef BIQUADRIS_BLOCK_H
#define BIQUADRIS_BLOCK_H
#include <utility>
#include <memory>
#include <vector>
#include "Enums.h"
#include "Subject.h"
#include "Cell.h"

class Block: public Observer, public Subject{
    // Check if the Block is deleted
    bool deleted;
    // "level" tracks the the level number when the Block is created
    int level;
    static void getPos(std::unique_ptr<std::pair<int, int>[]>& poses, const int num, int& row, int& col, int&negWidth);
    static void getPos(std::vector<Cell> &cells, int& row, int& left, int&right);
    static void Clockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num);
    static void counterClockwise(std::unique_ptr<std::pair<int, int>[]>& poses, const int num);
    
protected:
    std::vector<Cell> cells;
    const int numCells;
  
public:
    
    Block(const int level, const int numCells, Observer* obs);

    void notify() override;

    //Get info functions
    // checkExist() returns the boolean value of whether the Block exists on the Board
    bool checkExist();
    // getLevel() returns the level of the the Block when it's been created
    int getLevel();

    //Movement funcions
    void down();
    void left();
    void right();
    void Clockwise();
    void counterClockwise();
    // calcPosition(MoveType type) returns the position of the block if certain move is done
    std::unique_ptr<std::pair<int, int>[]> calcPosition(const MoveType type)const;
    static void furtherCalculates(const MoveType type, std::unique_ptr<std::pair<int, int>[]>& calculates, const int numCells);
    std::vector<Cell>& getCells();
    
    int getSize() const{
        return numCells;
    }
    
    virtual ~Block() = 0;
    int getState() const override{
        return deleted;
    }
};


#endif //BIQUADRIS_BLOCK_H
