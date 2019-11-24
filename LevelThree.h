#ifndef BIQUADRIS_LEVELTHREE_H
#define BIQUADRIS_LEVELTHREE_H


class LevelThree : public Level {
public:
    // Constructor
    LevelThree(unsigned int seed = 0);
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock() override;
};


#endif //BIQUADRIS_LEVELTHREE_H
