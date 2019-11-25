#include "LevelTwo.h"
#include "Enums.h"
#include <cstdlib>

// Constructor
LevelTwo::LevelTwo(unsigned int seed = 0) : seed{seed}, star{false}, heavy{false} {
    srand(seed);
}

bool LevelTwo::addStar() {
    return star;
}

bool LevelTwo::applyHeavy() {
    return heavy;
}

// Override the nextBlock() method in the base class to select the shape of next Block dropped
BlockType LevelTwo::nextBlock() {
    int r = rand() % 7;
    if (r == 0) {
        return BlockType::IBlock;
    } else if (r == 1) {
        return BlockType::JBlock;
    } else if (r == 2) {
        return BlockType::LBlock;
    } else if (r == 3) {
        return BlockType::OBlock;
    } else if (r == 4) {
        return BlockType::SBlock;
    } else if (r == 5) {
        return BlockType::TBlock;
    } else {
        return BlockType::ZBlock;
    }
}
