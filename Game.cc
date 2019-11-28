#include "Game.h"
void Game::newRound(){
    int times = 0;
    c.getCommand(std::cin, currentCommand, times);
    while(true){
        //Exit if command is game is over
        if(currentCommand == Command::quit) return;
        if(currentCommand == Command::drop){
            //Check if successful only at drop in the run function eventually
            players[currentPlayer].drop();
            //Get command after drop
            c.getCommand(std::cin, currentCommand, times);
            if(currentCommand == Command::blind || currentCommand == Command::heavy || currentCommand == Command::force){
                specialEffects();
                c.getCommand(std::cin, currentCommand, times);
            }
            //Always return after drop, no matter success or fail. Check success or fail in the upper function.
            return;
        }
        excecute();
    }
}

void Game::excecute(){
    Player* p = &players[currentPlayer];
    switch (currentCommand){
        case Command::left:{
            p->left();break;
        }
        case Command::right:{
            p->right();break;
        }
        case Command::down:{
            p->down();break;
        }
        case Command::clockwise:{
            p->rotateClockwise();break;
        }
        case Command::counterclockwise:{
            p->rotateCounterClockwise();break;
        }
        case Command::levelup:{
            try{
                p->levelUp();
            }catch(const char* m){
                std::cout << m << std::endl;
            }
            break;
        }
        case Command::leveldown:{
            try{
                p->levelDown();
            }catch(const char* m){
                std::cout << m << std::endl;
            }break;
        }
        case Command::force:
        case Command::blind:
        case Command::heavy:{
            std::cout<<"Cannot excecute special effects, the block is not dropped yet."<<std::endl;
            break;
        } 
        case Command::restart:{
            restart();
            break;
        }
        //ONLY Randoma, norandom, sequence are not implemented and need some discussions about level !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        case Command::norandom:
        case Command::random:
        case Command::sequence:
        default:{
            setBlockType();
        }
    }
    p->notifyObservers();
}

void Game::restart(){
    players[0].restart();
    players[1].restart();
    currentPlayer = 0;
}
void Game::setBlockType(){
    players[currentPlayer].restriction = Restriction::forced;
    switch (currentCommand){
        case Command::I:{
            players[currentPlayer].forcedType = BlockType::IBlock; break;
        }
        case Command::J:{
            players[currentPlayer].forcedType = BlockType::JBlock; break;
        }
        case Command::L:{
            players[currentPlayer].forcedType = BlockType::LBlock; break;
        }
        case Command::O:{
            players[currentPlayer].forcedType = BlockType::OBlock; break;
        }
        case Command::S:{
            players[currentPlayer].forcedType = BlockType::SBlock; break;
        }
        case Command::T:{
            players[currentPlayer].forcedType = BlockType::TBlock; break;
        }
        case Command::Z:{
            players[currentPlayer].forcedType = BlockType::ZBlock; break;
        }
    }
}

void Game::specialEffects(){
    int times = 0;
    if(players[currentPlayer].getLinesDeleted() >= 2){
        switch(currentCommand){
            case Command::blind:{
                players[!currentPlayer].restriction = Restriction::blind;
            }
            case Command::heavy:{
                players[!currentPlayer].restriction = Restriction::specialHeavy;
            }
            default:{
                players[!currentPlayer].restriction = Restriction::forced;
                while(true){
                    try{
                        c.getCommand(std::cin, currentCommand, times);
                        players[!currentPlayer].forcedType = c.getBlockType(currentCommand);
                    }catch(const char*m){
                        std::cout << m << std::endl;
                        continue;
                    }
                    break;
                }
            }
        }
    }
    else{
        std::cout << "You have only deleted " <<players[currentPlayer].getLinesDeleted()
            <<" lines this time, you are not allowed to use special effects"<< std::endl;
    }
}

void Game::endGame(){
    std::string loser,winner;
    if(players[0].getState() && players[1].getState()){
        std::cout << "No one lost, no one won."<<std::endl;
        return;
    }
    if(!players[0].getState()){
        loser = players[0].getName();
        winner = players[1].getName();
    }
    else if(!players[1].getState()) {
        loser = players[1].getName();
        winner = players[0].getName();
    }
    std::cout << loser <<" has lost."<<std::endl;
    std::cout << winner <<" has won."<<std::endl;
}

int Game::Init(const std::string name1, const std::string name2, const int seed, const std::string script1, const std::string script2, 
    const int startLevel, const int height = 15, const int width = 11){
    if(startLevel > 4 || startLevel < 0){
         std::cout << "startlevel is out of range." << std::endl;
         return -1;
    }
    displays.emplace_back(std::make_unique(TextDisplay{height, width}));
    if(script1.length())
        players.emplace_back(name1, startLevel, displays, height, width, seed, &script1);
    else 
        players.emplace_back(name1, startLevel, displays, height, width, seed);
    if(script2.length())
        players.emplace_back(name2, startLevel, displays, height, width, seed, &script2);
    else 
        players.emplace_back(name2, startLevel, displays, height, width, seed);
    currentPlayer = 0;
    return 0;
}

void Game::run(){
    while(true){
        while(true){
            newRound();
            if(currentCommand == Command::quit) break;
            //End the game if not successful
            if(players[currentPlayer].getState() == false){
                endGame();
                restart();
                break;
            }
            currentPlayer = !currentPlayer;
        }
        if(currentCommand == Command::quit){
            break;
            endGame();
        }
    }
}