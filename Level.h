#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H
#include <fstream>
#include "Enums.h"

class Level {
protected:
    std::ifstream in;
    
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool star;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool heavy;
    bool randomApply;
    bool randomSwitch;
    
public:
    const int level;
    // Constructor
    Level(unsigned int seed, bool star, bool heavy, int level):
        seed{seed}, star{star}, heavy{heavy}, level{level},
        randomApply{false}, randomSwitch{true}{}
    bool addStar()const{ return star; };
    bool applyHeavy()const { return heavy;};
    BlockType readNextBlock();
    
    //Virtual methods below:
    virtual BlockType nextBlock() = 0;
    virtual ~Level(){}
    virtual bool setRandom(){ return false; }
    virtual bool unsetRandom(const std::string file){ return false;}
};


#endif //BIQUADRIS_LEVEL_H
