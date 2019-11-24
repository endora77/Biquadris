#ifndef BIQUADRIS_LEVELONE_H
#define BIQUADRIS_LEVELONE_H


class LevelOne : public Level {
    unsigned int seed;
    const bool addStar;
    const bool applyHeavy;
public:
    // Constructor
    LevelOne(unsigned int seed = 0);
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock() override;
};


#endif //BIQUADRIS_LEVELONE_H
