#ifndef JBLOCK_H
#define JBLOCK_H
#include "../Block.h"
#include "../Cell.h"
#include "../Enums.h"

class JBlock: public Block{
public:
    JBlock(const int row, const int col, const int level);

    std::vector<Cell>& getCells() override;
};

#endif

