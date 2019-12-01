#include "TBlock.h"

TBlock::TBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col, BlockType::TBlock, this);
    cells.emplace_back(row, col + 1, BlockType::TBlock, this);
    cells.emplace_back(row, col + 2, BlockType::TBlock, this);
    cells.emplace_back(row + 1, col + 1, BlockType::TBlock, this);
}