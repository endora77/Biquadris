#ifndef BIQUADRIS_LEVELTHREE_H
#define BIQUADRIS_LEVELTHREE_H
#include "Level.h"
#include <fstream>

class LevelThree : public Level {
public:
    // Constructor
    LevelThree(unsigned int seed = 0);
    BlockType nextBlock() override;
    bool setRandom()override;
    bool unsetRandom(const std::string file)override;
};

#endif //BIQUADRIS_LEVELTHREE_H
