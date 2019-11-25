#ifndef BIQUADRIS_LEVELFOUR_H
#define BIQUADRIS_LEVELFOUR_H


class LevelFour : public Level {
public:
    // Constructor
    LevelFour(unsigned int seed = 0);
    // Override the addStar() method and return a boolean value of whether addStar effect will be applied
    bool addStar() override;
    // Override the applyHeavy() method and return a boolean value of whether the heavy effect will be applied
    bool applyHeavy() override;
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock();
};


#endif //BIQUADRIS_LEVELFOUR_H
