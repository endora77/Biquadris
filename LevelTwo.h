#ifndef BIQUADRIS_LEVELTWO_H
#define BIQUADRIS_LEVELTWO_H


class LevelTwo : public Level {
public:
    // Override the nextBlock() method in the base class to select the shape of next Block dropped
    BlockType nextBlock() override;
    // Override the heavy() method in the base class if heavy effect is applied
    bool heavy() override;
    // Override the addStar() method in the base class to add a star in the middle column
    bool addStar() override;
};


#endif //BIQUADRIS_LEVELTWO_H
