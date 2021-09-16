#ifndef BIQUADRIS_DISPLAY_H
#define BIQUADRIS_DISPLAY_H
#include <vector>
#include <string>
#include "Observer.h"
#include "Enums.h"

//Not safe to include, since Game includes display
#include "Game.h"

class Display : public Observer {
protected:
    Game *game;
    Display(Game* game): game{game}{}
    // Methods
    virtual void init(std::string name) = 0;
    virtual void fillBlind() = 0;
    virtual void fillBlock() = 0;
    virtual void fillTopInfo() = 0;
    virtual void fillNextBlock() = 0;
};

#endif //BIQUADRIS_DISPLAY_H
