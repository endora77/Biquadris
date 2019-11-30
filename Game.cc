#include "Game.h"
#include "Player.h"
using namespace std;
//OK
void Game::readNext(std::string& cmd){
    if((*in) >>cmd){}
    else{
        if(in == &temp_in){
            in = &original_in;
            temp_in.close();
        }
    }
}

//OK
void Game::newRound(){
 int times = 0;
 std::string cmd;
 readNext(cmd);
 c.getCommand(cmd, currentCommand, times);
 while(true){
     if(currentCommand == Command::quit) return;
     if(currentCommand == Command::drop){
         players[currentPlayer].drop();
         readNext(cmd);
         c.getCommand(cmd, currentCommand, times);
         if(currentCommand == Command::blind || currentCommand == Command::heavy || currentCommand == Command::force){
             specialEffects();
         }
         //Always return after drop, no matter success or fail. Check success or fail in the upper function.
         return;
     }
     readNext(cmd);
     c.getCommand(cmd, currentCommand, times);
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
                 out << m << std::endl;
             }
             break;
         }
         case Command::leveldown:{
             try{
                 p->levelDown();
             }catch(const char* m){
                 out << m << std::endl;
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
     std::string cmd;
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
                         readNext(cmd);
                         c.getCommand(cmd, currentCommand, times);
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
     else{
         out << "You have only deleted " <<players[currentPlayer].getLinesDeleted()
             <<" lines this time, you are not allowed to use special effects"<< std::endl;
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
             endGame();
             break;
         }
     }
 }
