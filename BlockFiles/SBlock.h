#ifndef SBLOCK_H
#define SBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

// S-block is in the form of
//  SS
// SS

class SBlock: public Block{
public:
    SBlock(const int row, const int col, const int level, Observer* obs);
    ~SBlock()override{}
};

#endif

