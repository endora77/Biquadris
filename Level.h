#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H


class Level {
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool addStar;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool applyHeavy;
public:
    virtual BlockType nextBlock() = 0;
};


#endif //BIQUADRIS_LEVEL_H
