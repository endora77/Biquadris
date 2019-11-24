#include "ZBlock.h"
ZBlock::ZBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col, BlockType::ZBlock);
    cells.emplace_back(row, col + 1, BlockType::ZBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::ZBlock);
    cells.emplace_back(row + 1, col + 2, BlockType::ZBlock);
}
