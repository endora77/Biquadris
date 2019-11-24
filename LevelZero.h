#ifndef BIQUADRIS_LEVELZERO_H
#define BIQUADRIS_LEVELZERO_H
#include <iostream>


class LevelZero : public Level {
    // Tell the Board whether addStar effect will apply in this level
    const bool addStar;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool applyHeavy;
public:
    // Constructor
    LevelZero();
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock(std::istream &in) override;
};


#endif //BIQUADRIS_LEVELZERO_H