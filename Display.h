#ifndef BIQUADRIS_DISPLAY_H
#define BIQUADRIS_DISPLAY_H
#include <vector>
#include <string>

template<typename T>
class Display {
    Board *board;
    std::vector<std::vector<T>> theDisplay;

    // Methods
    virtual void init(std::string name) = 0;
    virtual void fillBlind() = 0;
    virtual void fillBlock() = 0;
    virtual void fillTopInfo() = 0;
    virtual void fillNextBlock() = 0;
};


#endif //BIQUADRIS_DISPLAY_H
