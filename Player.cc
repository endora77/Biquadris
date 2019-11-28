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
    }
}

void Player::getNextBlock(){
    BlockType type;
    if(restriction == Restriction::forced) type = forcedType;
    else type = level->nextBlock();
    currentBlock = board->newBlock(type, 0, 3);
}

void Player::down(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    if(board->checkPosition(pos)){
        board->eraseBlock(currentBlock);
        currentBlock->down();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) down();
    }
}

void Player::left(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveLeft);
    if(board->checkPosition(pos)){
        board->eraseBlock(currentBlock);
        currentBlock->left();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) down();
        if(restriction == Restriction::specialHeavy){
            down();
            down();
        }
    } 
   
}

void Player::right(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveRight);
    if(board->checkPosition(pos)){
        board->eraseBlock(currentBlock);
        currentBlock->right();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) down();
        if(restriction == Restriction::specialHeavy){
            down();
            down();
        }
    } 
}

void Player::rotateClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(board->checkPosition(pos)){
        board->eraseBlock(currentBlock);
        currentBlock->Clockwise();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) down();
    } 
}

void Player::rotateCounterClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(board->checkPosition(pos)){
        board->eraseBlock(currentBlock);
        currentBlock->counterClockwise();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) down();
    }
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
    resetRestrictions();
    if(board->checkTop()) success = false;
}

int Player::getScore()const{
    return board->totalScore;
}

string Player::getName()const{
    return name;
}

void Player::restart(){
    success = true;
    board->restart();
}

void Player::resetRestrictions(){
    restriction = Restriction::noRestriction;
}


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