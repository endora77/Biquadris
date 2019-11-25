#include "LevelThree.h"
#include "Enums.h"
#include <cstdlib>

// Constructor
LevelThree::LevelThree(unsigned int seed = 0) : seed{seed}, star{false}, heavy{true} {
    srand(seed);
}

bool LevelThree::addStar() {
    return star;
}

bool LevelThree::applyHeavy() {
    return heavy;
}

BlockType LevelThree::nextBlock() {
    int r = rand() % 9;
    if ((r == 0) || (r == 1)) {
        return BlockType::SBlock;
    } else if ((r == 2) || (r == 3)) {
        return BlockType::ZBlock;
    } else if (r == 4) {
        return BlockType::LBlock;
    } else if (r == 5) {
        return BlockType::IBlock;
    } else if (r == 6) {
        return BlockType::OBlock;
    } else if (r == 7) {
        return BlockType::TBlock;
    } else {
        return BlockType::JBlock;
    }
}
