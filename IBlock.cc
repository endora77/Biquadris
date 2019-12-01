#include "IBlock.h"

IBlock::IBlock(const int row, const int col, const int level, Observer* obs): Block{level, 4, obs}{
    cells.emplace_back(row, col, BlockType::IBlock, this);
    cells.emplace_back(row, col + 1, BlockType::IBlock, this);
    cells.emplace_back(row, col + 2, BlockType::IBlock, this);
    cells.emplace_back(row, col + 3, BlockType::IBlock, this);
}
