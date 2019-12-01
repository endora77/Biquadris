#ifndef STARBLOCK_H
#define STARBLOCK_H
#include "Block.h"

// Z-block is in the form of
// ZZ
//  ZZ

class StarBlock: public Block{
public:
    StarBlock(const int row, const int col, const int level, Observer* obs);
    ~StarBlock()override{}
};

#endif
