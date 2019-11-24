#ifndef IBLOCK_H
#define IBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

// I-block is in the form of 
// IIII.

class IBlock: public Block{
public:
    IBlock(const int row, const int col, const int level, Observer* obs);

};

#endif

