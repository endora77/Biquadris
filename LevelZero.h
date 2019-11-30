#ifndef BIQUADRIS_LEVELZERO_H
#define BIQUADRIS_LEVELZERO_H
#include <iostream>
#include <fstream>
#include "Level.h"

class LevelZero : public Level {
    std::string file;
public:
    // Constructor
    LevelZero(const std::string file);
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock();
};


#endif //BIQUADRIS_LEVELZERO_H
