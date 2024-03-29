#include "LevelZero.h"
#include "Enums.h"
#include <fstream>

using namespace std;

// Constructor
LevelZero::LevelZero(const string file) : Level{0, false, false, 0},file{file} {
    in.open(file.c_str());
    if(!in)throw "Cannot open file for LevelZero";
}

// nextBlock() reads a string from an ifstream and returns the BlockType of the next block
BlockType LevelZero::nextBlock() {
    return readNextBlock();
}


