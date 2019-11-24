#include "SBlock.h"

SBlock::SBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col + 1, BlockType::SBlock);
    cells.emplace_back(row, col + 2, BlockType::SBlock);
    cells.emplace_back(row + 1, col, BlockType::SBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::SBlock);
}
