#include "LBlock.h"

LBlock::LBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::LBlock);
    cells.emplace_back(row + 1, col, BlockType::LBlock);
    cells.emplace_back(row + 1, col - 1, BlockType::LBlock);
    cells.emplace_back(row + 1, col - 2, BlockType::LBlock);
}

std::vector<Cell>& LBlock::getCells(){
    return cells;
}

