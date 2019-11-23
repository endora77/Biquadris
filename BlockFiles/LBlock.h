#ifndef LBLOCK_H
#define LBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

class LBlock: public Block{
public:
    LBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif

