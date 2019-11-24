#include "LevelZero.h"
#include "Enums.h"
#include <fstream>

using namespace std;

// Constructor
LevelZero::LevelZero() : addStar{false}, applyHeavy{false} {}

// nextBlock() reads a string from an istream and returns the BlockType of the next block
BlockType LevelZero::nextBlock(istream &in) {
    string block;
    if (in >> block) {
        if (block == "IBlock") {
            return BlockType::IBlock;
        }
        if (block == "JBlock") {
            return BlockType::JBlock;
        }
        if (block == "LBlock") {
            return BlockType::LBlock;
        }
        if (block == "OBlock") {
            return BlockType::OBlock;
        }
        if (block == "SBlock") {
            return BlockType::SBlock;
        }
        if (block == "TBlock") {
            return BlockType::TBlock;
        }
        if (block == "ZBlock") {
            return BlockType::ZBlock;
        }
    }
}

