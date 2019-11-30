#ifndef JBLOCK_H
#define JBLOCK_H
#include "../Block.h"

// JBlock is in the form of 
// J
// JJJ

class JBlock: public Block{
public:
    JBlock(const int row, const int col, const int level, Observer* obs);
    ~JBlock()override{}
};

#endif

