 #ifndef GAME_H
 #define GAME_H
//These two are safe
 #include "Command.h"
 #include <string>

//Player does not need to know about game, so it's safe
 #include "Player.h"
#include "Observer.h"
class Player;
class Display;
class Game final{
    std::istream *in;
    std::ifstream temp_in;
    std::istream &original_in;
    std::ostream &out;
    std::vector<std::unique_ptr<Observer*>> displays;
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
    void readNext(std::string& cmd);
 public:
    //Init OK
    int Init(const std::string name1, const std::string name2, const int seed, const std::string script1, const std::string script2,
             const int startLevel, std::vector<std::unique_ptr<Observer>>displays, const int height, const int width){
        in = &original_in;
        if(script1.length())
            players.emplace_back(name1, startLevel, displays, height, width, seed, script1);
        else
            players.emplace_back(name1, startLevel, displays, height, width, seed);
        if(script2.length())
            players.emplace_back(name2, startLevel, displays, height, width, seed, script2);
        else
            players.emplace_back(name2, startLevel, displays, height, width, seed);
        currentPlayer = 0;
        return 0;
    }
    void run();
    Game(std::istream &in, std::ostream &out): original_in{in}, out{out}, c{out}{}
    friend class TextDisplay;

};


#endif
// #ifndef GAME_H
// #define GAME_H
// #include "Player.h"
// #include "Display.h"
// #include "TextDisplay.h"
// #include "Command.h"
// #include <string>

// class Game{
//     std::istream *in;
//     std::ifstream temp_in;
//     std::istream &original_in;
//     std::ostream &out;
//     std::vector<std::unique_ptr<Display>> displays;
//     std::vector<Player> players;
//     int currentPlayer;
//     Command c;
//     Command::type currentCommand;
//     void newRound();
//     void excecute();
//     void restart();
//     void setBlockType();
//     void specialEffects();
//     void endGame();
//     void readNext(std::string& cmd);
//  public:
//     int Init(const std::string name1, const std::string name2, const int seed, const std::string script1, const std::string script2, 
//         const int startLevel, const int height = 15, const int width = 11);
//     void run();
//     Game(std::istream &in, std::ostream &out): original_in{in}, out{out}{}
//     friend class TextDisplay;

// };


// #endif
