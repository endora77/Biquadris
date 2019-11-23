#include "TBlock.h"

TBlock::TBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::TBlock);
    cells.emplace_back(row, col + 1, BlockType::TBlock);
    cells.emplace_back(row, col + 2, BlockType::TBlock);
    cells.emplace_back(row + 1, col + 1, BlockType::TBlock);
}

std::vector<Cell>& TBlock::getCells(){
    return cells;
}

