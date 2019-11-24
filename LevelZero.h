#ifndef BIQUADRIS_LEVELZERO_H
#define BIQUADRIS_LEVELZERO_H
#include <iostream>
#include <fstream>


class LevelZero : public Level {
public:
    // Constructor
    LevelZero();
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock(std::iftream &in) override;
};


#endif //BIQUADRIS_LEVELZERO_H