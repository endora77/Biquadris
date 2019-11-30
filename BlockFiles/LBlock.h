#ifndef LBLOCK_H
#define LBLOCK_H
#include "../Block.h"

// L-block is in the form of
//   L
// LLL

class LBlock: public Block{
public:
    LBlock(const int row, const int col, const int level, Observer* obs);
    ~LBlock()override{}
};

#endif

