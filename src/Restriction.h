#ifndef BIQUADRIS_RESTRICTION_H
#define BIQUADRIS_RESTRICTION_H


class Restriction {
    // Check if force command is called by the player
    bool forced;
    // Stores the type of the Block if command force is called
    BlockType forcedType;
    // Check if the temparory heavy effect need to apply
    bool specialHeavy;
    // Check if the blind effect need to apply
    bool blind;
public:
    virtual void forced() = 0;
    virtual BlockType getForcedType() = 0;
    virtual blinded() = 0;
    virtual heavied() = 0;
};


#endif //BIQUADRIS_RESTRICTION_H
