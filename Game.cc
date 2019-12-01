#include "Game.h"
#include "Player.h"
using namespace std;

void Game::readNext(std::string& cmd){
    if((*in) >>cmd){}
    else{
        if(in == &temp_in){
            in = &original_in;
            temp_in.close();
        }
    }
}

void Game::newRound(){
    std::string cmd;
    players[currentPlayer].notifyObservers();

    while(true){
        int times = 1;
        do{
            readNext(cmd);
        }while(!c.getCommand(cmd, currentCommand, times));
        if(currentCommand == Command::quit) return;
        excecute(times);
        if(currentCommand == Command::drop){
            specialEffects();
            return;
        }
    }
}

void Game::excecute(const int times){
     Player* p = &players[currentPlayer];
     switch (currentCommand){
         case Command::drop:{
             p->drop();
             break;
         }
         case Command::left:{
             for(int i = 0; i < times; i++)p->left();
             break;
         }
         case Command::right:{
             for(int i = 0; i < times; i++)p->right();
             break;
         }
         case Command::down:{
             for(int i = 0; i < times; i++)p->down();
             break;
         }
         case Command::clockwise:{
             for(int i = 0; i < times; i++)p->rotateClockwise();
             break;
         }
         case Command::counterclockwise:{
             for(int i = 0; i < times; i++)p->rotateCounterClockwise();
             break;
         }
         case Command::levelup:{
             for(int i = 0; i < times; i++){
                 try{
                     p->levelUp();
                 }catch(const char* m){
                     out << m << std::endl;
                     p->levelDown();
                 }
             }
             break;
         }
         case Command::leveldown:{
             for(int i = 0; i < times; i++){
                 try{
                     p->levelDown();
                 }catch(const char* m){
                     out << m << std::endl;
                     p->levelUp();
                 }
             }
             break;
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
         case Command::norandom:{
             std::string file_name;
             readNext(file_name);
             players[currentPlayer].norand(file_name);
             break;
         }
         case Command::random:{
             players[currentPlayer].rand();
         }
         case Command::sequence:{
             std::string file_name;
             readNext(file_name);
             temp_in.open(file_name);
             if(!temp_in.is_open())
                 out << "Cannot open the sequence file " <<file_name<< std::endl;
             in = &temp_in;
         }
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
     players[0].playing = true;
     players[1].playing = false;
     players[currentPlayer].getNextBlock();
     players[!currentPlayer].getNextBlock();
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
     if(players[currentPlayer].getLinesDeleted() >= 2){
         out << "You have deleted "<<players[currentPlayer].getLinesDeleted()<<", now you can use special effects."<<endl;
         int times = 0;
         std::string cmd;
         readNext(cmd);
         do{
             readNext(cmd);
         }while(!c.getCommand(cmd, currentCommand, times));
         switch(currentCommand){
             case Command::noeffect:break;
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
                         readNext(cmd);
                         do{
                             readNext(cmd);
                         }while(!c.getCommand(cmd, currentCommand, times));
                         players[!currentPlayer].forcedType = c.getBlockType(currentCommand);
                     }catch(const char*m){
                         out << m << std::endl;
                         continue;
                     }
                     break;
                 }
             }
         }
     }
 }

 void Game::endGame(){
     std::string loser,winner;
     if(players[0].getState() && players[1].getState()){
         out << "No one lost, no one won."<<std::endl;
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
     out << loser <<" has lost."<<std::endl;
     out << winner <<" has won."<<std::endl;
 }

void Game::switchPlayer(){
    currentPlayer = !currentPlayer;
    players[currentPlayer].playing = true;
    players[!currentPlayer].playing = false;
}

 void Game::run(){
     while(true){
         while(true){
             newRound();
             if(!players[currentPlayer].getNextBlock()){
                 //players[currentPlayer].nextType
                 out << "Not enough space for the next block for "<<players[currentPlayer].getName()<<" with block type"<< endl;
                 endGame();
                 restart();
                 break;
             }
             if(currentCommand == Command::quit) break;
             //End the game if not successful
             if(players[currentPlayer].getState() == false){
                 endGame();
                 restart();
                 break;
             }
             switchPlayer();
         }
         if(currentCommand == Command::quit){
             endGame();
             break;
         }
     }
 }
