#ifndef BIQUADRIS_DISPLAY_H
#define BIQUADRIS_DISPLAY_H
#include <vector>

template<typename T>class Display {
    Board *board;
    std::vector<std::vector<T>> theDisplay;

    // Methods
    virtual void fillBlind() = 0;
    virtual void fillBlock() = 0;
    virtual void updateScore() = 0;
    virtual void updateLevel() = 0;
    virtual void fillNextBlock() = 0;
};


#endif //BIQUADRIS_DISPLAY_H
