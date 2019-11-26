#ifndef TBLOCK_H
#define TBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

// T-block is in the form of
// TTT
//  T

class TBlock: public Block{
public:
    TBlock(const int row, const int col, const int level, Observer* obs);
    ~TBlock()override{}
};

#endif

