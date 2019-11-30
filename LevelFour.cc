#include "LevelFour.h"
#include "Enums.h"
#include <cstdlib>
#include <fstream>

LevelFour::LevelFour(unsigned int seed) : Level{seed, true, true, 4} {
    randomApply = true;
    srand(seed);
}

BlockType LevelFour::nextBlock() {
    if(!randomSwitch){
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
    }else{
        return readNextBlock();
    }
}

bool LevelFour::setRandom(){
    if(randomSwitch) throw "The sequence is already random.";
    in.close();
    randomSwitch = true;
    return true;
}

bool LevelFour::unsetRandom(const std::string file){
    if(!randomSwitch) throw "The sequence is already not random.";
    in.open(file.c_str());
    if(!in.is_open()) throw "Cannot open file in levelthree";
    randomSwitch = false;
    return true;
}
