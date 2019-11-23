#include "IBlock.h"

IBlock::IBlock(const int row, const int col, const int level): Block{level, 4}{
    cells.emplace_back(row, col, BlockType::IBlock);
    cells.emplace_back(row, col + 1, BlockType::IBlock);
    cells.emplace_back(row, col + 2, BlockType::IBlock);
    cells.emplace_back(row, col + 3, BlockType::IBlock);
}

std::vector<Cell>& IBlock::getCells(){
    return cells;
}

