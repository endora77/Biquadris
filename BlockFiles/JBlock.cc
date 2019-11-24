#include "JBlock.h"

JBlock::JBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col, BlockType::JBlock);
    cells.emplace_back(row + 1, col, BlockType::JBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::JBlock);
    cells.emplace_back(row + 1, col + 2, BlockType::JBlock);
}

