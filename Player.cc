#include "Player.h"
using namespace std;

//Throws an error
void Player::setLevel(const int l, int seed){
    switch(l){
        case 0:{
            level = make_unique<Level>(new LevelZero{});
            break;
        }
        case 1:{
            level = make_unique<Level>(new LevelOne{seed});
            break;
        }
        case 2:{
            level = make_unique<Level>(new LevelTwo{seed});
            break;
        }
        case 3:{
            level = make_unique<Level>(new LevelThree{seed});
            break;
        }
        case 4:{
            level = make_unique<Level>(new LevelFour{seed});
            break;
        }
        default: throw "Invalid level";
    }
}

void Player::getNextBlock(){
    BlockType type;
    if(forced) type = forcedType;
    else type = level->nextBlock();
    board->newBlock(type, 0, 3);
}

void Player::down(const int i){
    unique_ptr<pair<int, int>[]> pos = board->currentBlock->calcPosition(MoveType::moveDown);
    if(board->checkPosition(pos)) board->currentBlock->down();
}

void Player::left(const int i){
    unique_ptr<pair<int, int>[]> pos = board->currentBlock->calcPosition(MoveType::moveLeft, i);
    if(Player::checkPosition(pos)) currentBlock->left(i);
    if(restriction->specialHeavy) down(1);
}

void Player::right(const int i){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveRight, i);
    if(Player::checkPosition(pos)) currentBlock->right(i);
    if(restriction->specialHeavy) down(1);
}

void Player::rotateClockwise(const int i){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise, i);
    if(Player::checkPosition(pos)) 
        currentBlock = new Clockwise{*currentBlock};
}

void Player::rotateCounterClockwise(const int i){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveCounterClockwise, i);
    if(Player::checkPosition(pos))
     currentBlock = new rotateCounterClockwise{*currentBlock};
}

void Player::drop(){
    vector<Cell>& c = currentBlock->getCells();
    int lowest = gridH;
    int touchedCell = 0;
    for(int i = 0; i < 4; i++){
        pair<int, int> pos = c[i].getPosition();
        int temp = checkColBot(pos.second);
        if(temp < lowest){
            touchedCell = i;
            lowest = temp;
        } 
    }
    int shift = lowest - c[i].getPosition().first;
    currentBlock->down(shift);
}

void Player::forceOther(Player *otherPlayer, BlockType bType){
    // give otherPlayer's board the bType and let board changes the current
    // block's type to bType.
}

void Player::heavyOther(Player *otherPlayer){
    // applys heavy effect to otherPlayer until the block
    // drops
}

void Player::blindOther(Player *otherPlayer){
    
}

int Player::getScore(){
    return board->getScore();
}

string Player::getName(){
    return name;
}

Player::Player(string name, Board *board): name{name}, board{new board} {}
   