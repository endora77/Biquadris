#include "SBlock.h"

SBlock::SBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::SBlock);
    cells.emplace_back(row, col + 1, BlockType::SBlock);
    cells.emplace_back(row + 1, col - 1, BlockType::SBlock);
    cells.emplace_back(row + 1, col, BlockType::SBlock);
}

std::vector<Cell>& SBlock::getCells(){
    return cells;
}

