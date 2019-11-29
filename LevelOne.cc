#include "LevelOne.h"
#include "Enums.h"
#include <cstdlib>
#include <fstream>

// Constructor
LevelOne::LevelOne(unsigned int seed = 0) : Level(seed, false, false, 1) {
    srand(seed);
}

bool LevelOne::addStar() {
    return star;
}

bool LevelOne::applyHeavy() {
    return heavy;
}

BlockType LevelOne::nextBlock() {
    int r = rand() % 6;
    if (r == 0) {
        if (rand() % 2 == 0) {
            return BlockType::SBlock;
        } else {
            return BlockType::ZBlock;
        }
    } else if (r == 1) {
        return BlockType::TBlock;
    } else if (r == 2) {
        return BlockType::OBlock;
    } else if (r == 3) {
        return BlockType::LBlock;
    } else if (r == 4) {
        return BlockType::JBlock;
    } else {
        return BlockType::IBlock;
    }
}
