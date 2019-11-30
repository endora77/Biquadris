#ifndef BIQUADRIS_LEVELONE_H
#define BIQUADRIS_LEVELONE_H
#include "Level.h"
#include <fstream>


class LevelOne : public Level {
public:
    // Constructor
    LevelOne(unsigned int seed = 0);
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock() override;
};


#endif //BIQUADRIS_LEVELONE_H
