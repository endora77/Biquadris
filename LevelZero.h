#ifndef BIQUADRIS_LEVELZERO_H
#define BIQUADRIS_LEVELZERO_H
#include <iostream>
#include <fstream>


class LevelZero : public Level {
public:
    // Constructor
    LevelZero();
    // Override the addStar() method and return a boolean value of whether addStar effect will be applied
    bool addStar() override;
    // Override the applyHeavy() method and return a boolean value of whether the heavy effect will be applied
    bool applyHeavy() override;
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock(std::iftream &in);
};


#endif //BIQUADRIS_LEVELZERO_H