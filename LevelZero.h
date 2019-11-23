#ifndef BIQUADRIS_LEVELZERO_H
#define BIQUADRIS_LEVELZERO_H


class LevelZero : public Level {
public:
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock();
    // Override the heavy() method in the base class if heavy effect is applied
    bool heavy();
    // Override the addStar() method in the base class to add a star in the middle column
    bool addStar();
};


#endif //BIQUADRIS_LEVELZERO_H
