#ifndef TBLOCK_H
#define TBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

class TBlock: public Block{
public:
    TBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif

