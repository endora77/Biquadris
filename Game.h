#ifndef GAME_H
#define GAME_H
#include "Command.h"
#include <string>
#include "Player.h"
#include "Observer.h"

class Game final{
    bool printCommand = false;
    std::string recordHolder = "No one";
    int scoreRecord = 0;
    std::istream *in;
    std::ifstream temp_in;
    std::istream &original_in;
    std::ostream &out;
    std::vector<std::unique_ptr<Observer>> displays;
    std::vector<Player> players;
    int currentPlayer;
    Command c;
    Command::type currentCommand;
    
    //Drop a new block
    void newRound();
    
    //Excecute one specific command, in newRound(), there could be multiple excecutes
    void excecute(const int times);

    //Set the block type of the current dropping block
    void setBlockType();
    
    //See if any special effects are possible
    void specialEffects();
    
    //End the game
    void endGame();
    
    //Read the next command
    void readNext(std::string& cmd);
    
    //Switch the player
    void switchPlayer();
    
    //Restart the game
    void restart();
    
    //update the record
    bool updateRecord(int playerNumber);
    
    //Add a player
    int addPlayer(std::string name, const int startLevel,
                  std::vector<std::unique_ptr<Observer>>&displays,
                  const int height, const int width,
                  const unsigned int seed, const std::string script);
public:
    //Constructor
    Game(std::istream &in, std::ostream &out): original_in{in}, out{out}, c{out}{}
    
    //Initialize the game
    int Init(const std::string name1, const std::string name2, const int seed,
             const std::string script1, const std::string script2,
             const int startLevel, std::vector<std::unique_ptr<Observer>>displays,
             const int height, const int width);
    
    //Run the game
    void run();

    friend class TextDisplay;

};

#endif
