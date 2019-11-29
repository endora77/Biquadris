#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H
#include <fstream>
#include "Enums.h"

class Level {
protected:
    std::ifstream in;
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool star;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool heavy;
    bool randomApply;
    bool randomSwitch;
public:
    const int level;
    // Constructor
    Level(int seed, bool star, bool heavy, int level);
    virtual bool addStar() = 0;
    virtual bool applyHeavy() = 0;
    virtual BlockType nextBlock();

    //return false if it is not level 3 or 4, cannot setRandom or unset
    virtual bool setRandom(){
        return false;
    }
    virtual bool unsetRandom(const std::string file){
        return false;
    }
    BlockType readNextBlock();
};


#endif //BIQUADRIS_LEVEL_H
