#include "Player.h"
using namespace std;

//Throws an error
void Player::setLevel(const int l, int seed){
    switch(l){
        case 0:{
            level = make_unique<Level>(LevelZero{});
            break;
        }
        case 1:{
            level = make_unique<Level>(LevelOne{seed});
            break;
        }
        case 2:{
            level = make_unique<Level>(LevelTwo{seed});
            break;
        }
        case 3:{
            level = make_unique<Level>(LevelThree{seed});
            break;
        }
        case 4:{
            level = make_unique<Level>(LevelFour{seed});
            break;
        }
        default: throw "Invalid level";
    }
}

void Player::getNextBlock(){
    BlockType type;
    if(forced) type = forcedType;
    else type = level->nextBlock();
    currentBlock = board->newBlock(type, 0, 3);
}

void Player::down(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    if(board->checkPosition(pos)) currentBlock->down();
}

void Player::left(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveLeft);
    if(board->checkPosition(pos)) currentBlock->left();
    if(specialHeavy) down();
}

void Player::right(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveRight);
    if(board->checkPosition(pos)) currentBlock->right();
    if(specialHeavy) down();
}

void Player::rotateClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(board->checkPosition(pos)) currentBlock->Clockwise();
    if(specialHeavy) down();
}

void Player::rotateCounterClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(board->checkPosition(pos)) currentBlock->counterClockwise();
    if(specialHeavy) down();
}

void Player::drop(){
    vector<Cell>& c = currentBlock->getCells();
    int lowest = board->gridH;
    int touchedCell = 0;
    int i = 0; 
    for(;i < 4; i++){
        pair<int, int> pos = c[i].getPosition();
        int temp = board->checkColBot(pos.second);
        if(temp < lowest){
            touchedCell = i;
            lowest = temp;
        } 
    }
    int shift = lowest - c[i].getPosition().first;
    for(int j = 0; j < shift; j++)down();
}

int Player::getScore()const{
    return board->totalScore;
}

string Player::getName()const{
    return name;
}
void Player::reset(){
    
}
Player::Player(string name, Board *board): name{name}, board{new board} {}

// void Player::forceOther(Player *otherPlayer, BlockType bType){
//     // give otherPlayer's board the bType and let board changes the current
//     // block's type to bType.
// }

// void Player::heavyOther(Player *otherPlayer){
//     // applys heavy effect to otherPlayer until the block
//     // drops
// }

// void Player::blindOther(Player *otherPlayer){
    
// }