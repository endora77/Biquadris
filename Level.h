#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H


class Level {
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool star;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool heavy;
public:
    virtual bool addStar() = 0;
    virtual bool applyHeavy() = 0;
};


#endif //BIQUADRIS_LEVEL_H
