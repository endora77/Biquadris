#include "StarBlock.h"

StarBlock::StarBlock(const int row, const int col, const int level, Observer* obs): Block{level, 1, obs}{
    cells.emplace_back(row, col, BlockType::StarBlock);
}
