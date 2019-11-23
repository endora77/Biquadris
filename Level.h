#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H


class Level {
public:
    virtual BlockType nextBlock() = 0;
    virtual bool heavy() = 0;
    virtual bool addStar() = 0;
};


#endif //BIQUADRIS_LEVEL_H
