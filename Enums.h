#ifndef BIQUADRIS_ENUMS_H
#define BIQUADRIS_ENUMS_H

enum class BlockType{LBlock = 0, IBlock, JBlock, OBlock, SBlock, ZBlock, TBlock, StarBlock};

enum class MoveType{moveDown = 0, moveLeft, moveRight, moveClockwise, moveCounterClockwise};

enum class Restriction{forced = 0, blind, specialHeavy, noRestriction};

#endif //BIQUADRIS_ENUMS_H
 
