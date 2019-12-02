#ifndef BIQUADRIS_LEVEL_H
#define BIQUADRIS_LEVEL_H
#include <fstream>
#include "Enums.h"

class Level {
protected:
    std::ifstream in;
    //Seed for randomness
    unsigned int seed;
    // Tell the Board whether addStar effect will apply in this level
    const bool star;
    // Tell the Board whether heavy effect will apply when Block rotates in this level
    const bool heavy;
    bool randomApply;
    bool isRandom;
    
public:
    //Record the lvel
    const int level;
    // Constructor
    Level(unsigned int seed, bool star, bool heavy, int level):
        seed{seed}, star{star}, heavy{heavy}, level{level},
        randomApply{false}, isRandom{true}{}
    //Destructor
    virtual ~Level(){}
    
    //Returns if stars apply
    bool addStar()const{ return star; };
    //Returns if heavy apply
    bool applyHeavy()const { return heavy;};

    //Virtual methods below:
    //Returns the type of the next block
    virtual BlockType nextBlock() = 0;
    
    //Set and unset the randomness
    virtual bool setRandom(){ return false; }
    virtual bool unsetRandom(const std::string file){ return false;}
    
    //If there is a file available, read the next block, and determines if it is a valid block type
    BlockType readNextBlock();
};


#endif //BIQUADRIS_LEVEL_H
