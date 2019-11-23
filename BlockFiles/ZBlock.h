#ifndef ZBLOCK_H
#define ZBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"
class ZBlock: public Block{
public:
    ZBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif