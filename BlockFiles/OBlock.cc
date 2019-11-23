#include "OBlock.h"

OBlock::OBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::OBlock);
    cells.emplace_back(row, col + 1, BlockType::OBlock);
    cells.emplace_back(row + 1, col, BlockType::OBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::OBlock);
}

std::vector<Cell>& OBlock::getCells(){
    return cells;
}

