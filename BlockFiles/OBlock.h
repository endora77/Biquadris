#ifndef OBLOCK_H
#define OBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

class OBlock: public Block{
public:
    OBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif

