#include "Game.h"
#include "Player.h"
using namespace std;
int Game::Init(const std::string name1, const std::string name2, const int seed, const std::string script1, const std::string script2,
         const int startLevel, std::vector<std::unique_ptr<Observer>>displays, const int height, const int width){
    this->displays = std::move(displays);
    in = &original_in;
    if(addPlayer(name1, startLevel, this->displays, height, width, seed, script1)) return -1;
    if(addPlayer(name2, startLevel, this->displays, height, width, seed, script2)) return -1;
    currentPlayer = 0;
    players[currentPlayer].playing = true;
    players[!currentPlayer].playing = false;
    players[currentPlayer].getNextBlock();
    players[!currentPlayer].getNextBlock();
    return 0;
}

int Game::addPlayer(std::string name, const int startLevel, std::vector<std::unique_ptr<Observer>>&displays, const int height, const int width, const unsigned int seed, const std::string script){
    try{
        if(script.length())
            players.emplace_back(name, startLevel, displays, height, width, seed, script);
        else
            players.emplace_back(name, startLevel, displays, height, width, seed);
    }catch(std::string m){
        out << m <<std::endl;
        return -1;
    }
    return 0;
}

void Game::readNext(std::string& cmd){
    if((*in) >>cmd && cmd.size()){}
    else{
        if(in == &temp_in){
            in = &original_in;
            printCommand = false;
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
        }while(!c.getCommand(cmd, currentCommand, times, printCommand));
        if(currentCommand == Command::quit) return;
        if(currentCommand == Command::drop){
            players[currentPlayer].drop();
            players[currentPlayer].notifyObservers();
            specialEffects();
            for(int i = 1; i < times; i++){
                players[currentPlayer].getNextBlock();
                players[currentPlayer].drop();
                players[currentPlayer].notifyObservers();
                specialEffects();
            }
            return;
        }
        excecute(times);
        if(currentCommand != Command::drop)
            players[currentPlayer].notifyObservers();
    }
}

void Game::excecute(const int times){
     Player* p = &players[currentPlayer];
     switch (currentCommand){
         case Command::left:{
             p->left(times);break;
         }
         case Command::right:{
             p->right(times);break;
         }
         case Command::down:{
             p->down(times);break;
         }
         case Command::clockwise:{
             p->rotateClockwise(times);break;
         }
         case Command::counterclockwise:{
             p->rotateCounterClockwise(times);break;
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
             out<<"Cannot excecute special effects, the block is not dropped yet."<<std::endl;
             break;
         }
         case Command::restart:{
             endGame();
             restart();
             break;
         }
         case Command::norandom:{
             std::string file_name;
             readNext(file_name);
             try{
                 bool success = players[currentPlayer].norand(file_name);
                 if(!success) throw "Cannot use norandom for this level.";
             }catch(const char* m){
                 out << m << std::endl;
             }
             break;
         }
         case Command::random:{
             try{
                 bool success = players[currentPlayer].rand();
                 if(!success) throw "Cannot use random for this level.";
             }catch(const char* m){
                 out << m << std::endl;
             }
             break;
         }
         case Command::sequence:{
             std::string file_name;
             readNext(file_name);
             temp_in.open(file_name);
             if(!temp_in){
                 out << "Cannot open the sequence file " <<file_name<< std::endl;
                 break;
             }
             printCommand = true;
             in = &temp_in;
             break;
         }
         default:{
             setBlockType();
         }
     }
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
             players[currentPlayer].setBlock(BlockType::IBlock);break;
         }
         case Command::J:{
             players[currentPlayer].setBlock(BlockType::JBlock);break;
         }
         case Command::L:{
             players[currentPlayer].setBlock(BlockType::LBlock);break;
         }
         case Command::O:{
             players[currentPlayer].setBlock(BlockType::OBlock);break;
         }
         case Command::S:{
             players[currentPlayer].setBlock(BlockType::SBlock); break;
         }
         case Command::T:{
             players[currentPlayer].setBlock(BlockType::TBlock); break;
         }
         case Command::Z:{
             players[currentPlayer].setBlock(BlockType::ZBlock);break;
         }
     }
 }

 void Game::specialEffects(){
     if(players[currentPlayer].getLinesDeleted() >= 2){
         out << "You have deleted "<<players[currentPlayer].getLinesDeleted()<<", now you can use special effects."<<endl;
         int times = 0;
         std::string cmd;
         do{
             readNext(cmd);
         }while(!c.getCommand(cmd, currentCommand, times, printCommand));
         switch(currentCommand){
             case Command::noeffect:break;
             case Command::blind:{
                 players[!currentPlayer].restriction = Restriction::blind;break;
             }
             case Command::heavy:{
                 players[!currentPlayer].restriction = Restriction::specialHeavy;break;
             }
             case Command::force:{
                 players[!currentPlayer].restriction = Restriction::forced;
                 while(true){
                     try{
                         do{
                             readNext(cmd);
                         }while(!c.getCommand(cmd, currentCommand, times, printCommand));
                         BlockType t = c.getBlockType(currentCommand);
                         players[!currentPlayer].setBlock(t);
                     }catch(const char*m){
                         out << cmd <<": "<<m << std::endl;
                         continue;
                     }
                     break;
                 }
                 break;
             }
             default:{
                 out << "Not a valid special action, game continuing." << endl;
             }
         }
     }
 }
bool Game::updateRecord(int playerNumber){
    if(players[0].getScore() > scoreRecord){
        scoreRecord = players[playerNumber].getScore();
        recordHolder = players[playerNumber].getName();
        return true;
    }
    return false;
}

 void Game::endGame(){
     std::string topToucher, winningInfo;
     updateRecord(0);
     updateRecord(1);
     if(scoreRecord > 0){
         out << "Record: " <<std::endl;
         out << "   "<< "current record is "<< scoreRecord <<" held by " <<recordHolder<<"."<<std::endl;
     }
     out << "Game Result:"<<std::endl;
     if(players[0].getState() && players[1].getState()){
         out << "   "<< "No one touched the top of the board."<<std::endl;
     }
     else{
         if(!players[0].getState()){
             topToucher = players[0].getName();
         }
         else if(!players[1].getState()) {
             topToucher = players[1].getName();
         }
         out << "   "<< topToucher <<" has touched the top of the board."<<std::endl;
     }
     out << "   "<< players[0].getName() <<" scored "<< players[0].getScore()<<std::endl;
     out << "   "<< players[1].getName() <<" scored "<< players[1].getScore()<<std::endl;
     if(players[0].getScore() == players[1].getScore()){
         winningInfo = "it is a tie.";
     }else if(players[0].getScore() > players[1].getScore()){
         winningInfo = players[0].getName();
         winningInfo += " has won.";
     }else{
         winningInfo = players[1].getName();
         winningInfo += " has won.";
     }
     out << "   "<< "Basing on the score, "<<winningInfo <<std::endl;
 }

void Game::switchPlayer(){
    currentPlayer = !currentPlayer;
    players[currentPlayer].playing = true;
    players[!currentPlayer].playing = false;
}
char getTypeString(const BlockType type){
    switch(type){
        case BlockType::IBlock : return 'I';
        case BlockType::JBlock: return 'J';
        case BlockType::LBlock: return 'L';
        case BlockType::OBlock: return 'O';
        case BlockType::SBlock: return 'S';
        case BlockType::TBlock: return 'T';
        default: return 'Z';
    }
}
 void Game::run(){
     while(true){
         while(true){
             newRound();
             if(currentCommand == Command::quit){
                 endGame();
                 return;
             }
             if(!players[currentPlayer].getNextBlock()){
                 out << "Not enough space for the next block of type "<< getTypeString(players[currentPlayer].nextType)
                     <<" for "<<players[currentPlayer].getName() <<endl;
                 endGame();
                 restart();
                 break;
             }
             //End the game if not successful
             if(players[currentPlayer].getState() == false){
                 endGame();
                 restart();
                 break;
             }
             switchPlayer();
         }
     }
 }
