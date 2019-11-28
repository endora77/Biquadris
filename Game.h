#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Display.h"
#include "TextDisplay.h"
#include "Command.h"
#include <string>
class Game{
    std::vector<std::unique_ptr<Display>> displays;
    std::vector<Player> players;
    int currentPlayer;
    Command c;
    Command::type currentCommand;
    void newRound();
    void excecute();
    void restart();
    void setBlockType();
    void specialEffects();
    void endGame();
 public:
    int Init(const std::string name1, const std::string name2, const int seed, const std::string script1, const std::string script2, 
        const int startLevel, const int height = 15, const int width = 11);
    void run();

};

#endif