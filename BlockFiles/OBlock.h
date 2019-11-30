#ifndef OBLOCK_H
#define OBLOCK_H
#include "../Block.h"
// O-block is in the form of
// OO
// OO

class OBlock: public Block{
public:
    OBlock(const int row, const int col, const int level, Observer* obs);
    ~OBlock()override{}
};

#endif

