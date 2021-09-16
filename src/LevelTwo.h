#ifndef BIQUADRIS_LEVELTWO_H
#define BIQUADRIS_LEVELTWO_H
#include "Level.h"
#include <fstream>


class LevelTwo : public Level {
public:
    // Constructor
    LevelTwo(unsigned int seed = 0);
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock() override;
};

#endif //BIQUADRIS_LEVELTWO_H
