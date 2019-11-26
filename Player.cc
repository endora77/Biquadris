#include "player.h"
using namespace std;

void Player::newBlock(const BlockType type, const int row, const int col){
    switch(type){
        case BlockType::ZBlock: return new ZBlock{row, col, level->level, this};
        case BlockType::LBlock: return new LBlock{row, col, level->level, this};
        case BlockType::IBlock: return new IBlock{row, col, level->level, this};
        case BlockType::JBlock: return new JBlock{row, col, level->level, this};
        case BlockType::OBlock: return new OBlock{row, col, level->level, this};
        case BlockType::SBlock: return new SBlock{row, col, level->level, this};
        case BlockType::TBlock: return new TBlock{row, col, level->level, this};
        case BlockType::StarBlock: return new StarBlock{row, col, level->level, this};
    }
}

//Throws an error
void Player::setLevel(const int l, const BlockType type, int seed){
    delete level;
    switch(l){
        case 0:{
            level = new LevelZero{};
            nextType = level->nextBlock(blockFile);
            break;
        }
        case 1:{
            level = new LevelOne{seed};
            nextType = level->nextBlock();
            break;
        }
        case 2:{
            level = new LevelTwo{seed};
            nextType = level->nextBlock();
            break;
        }
        case 3:{
            level = new LevelThree{seed};
            nextType = level->nextBlock();
            break;
        }
        case 4:{
            level = new LevelFour{seed};
            nextType = level->nextBlock();
            break;
        }
        default: throw "Invalid level";
    }
}

void Player::getNextBlock(){
    BlockType type;
    if(restriction->forced) type = restriction->forcedType;
    else type = nextType;
    currentBlock = newBlock{type, 0, 3};
    blocks.push_back(currentBlock);
}
void Player::down(const int i){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown, i);
    if(Player::checkPosition(pos)) level->down(*currentBlock, i); 
}

void Player::left(const int i){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveLeft, i);
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
   