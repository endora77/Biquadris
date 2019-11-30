#include "Level.h"

// Constructor


BlockType Level::readNextBlock(){
    std::string block;
    if (in >> block) {
        if (block == "I") {
            return BlockType::IBlock;
        }
        if (block == "J") {
            return BlockType::JBlock;
        }
        if (block == "L") {
            return BlockType::LBlock;
        }
        if (block == "O") {
            return BlockType::OBlock;
        }
        if (block == "S") {
            return BlockType::SBlock;
        }
        if (block == "T") {
            return BlockType::TBlock;
        }
        if (block == "Z") {
            return BlockType::ZBlock;
        }
        throw "Not a valid block type";
    }else{
        in.clear();
        in.seekg(0, std::ios::beg);
        return readNextBlock();
    }
}
