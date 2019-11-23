#ifndef IBLOCK_H
#define IBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

class IBlock: public Block{
public:
    IBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif

