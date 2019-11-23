#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H


class Level {
public:
    BlockType nextBlock() = 0;
    bool heavy() = 0;
    bool addStar() = 0;
};


#endif //BIQUADRIS_LEVEL_H
