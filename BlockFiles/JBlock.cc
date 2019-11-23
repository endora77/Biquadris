#include "JBlock.h"

JBlock::JBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::JBlock);
    cells.emplace_back(row + 1, col, BlockType::JBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::JBlock);
    cells.emplace_back(row + 1, col + 2, BlockType::JBlock);
}

std::vector<Cell>& JBlock::getCells(){
    return cells;
}

