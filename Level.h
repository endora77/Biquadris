#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H
#include <fstream>
#include "Enums.h"

class Level {
protected:
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool star;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool heavy;
public:
    const int level;
    // Constructor
    Level(int seed, bool star, bool heavy, int level);
    virtual bool addStar() = 0;
    virtual bool applyHeavy() = 0;
    virtual BlockType nextBlock(std::ifstream &in);
    virtual BlockType nextBlock();
};


#endif //BIQUADRIS_LEVEL_H
