#include "OBlock.h"

OBlock::OBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col, BlockType::OBlock, this);
    cells.emplace_back(row, col + 1, BlockType::OBlock, this);
    cells.emplace_back(row + 1, col, BlockType::OBlock, this);
    cells.emplace_back(row + 1, col + 1, BlockType::OBlock, this);
}
