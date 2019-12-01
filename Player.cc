#include "Player.h"
using namespace std;

//Throws an error
void Player::setLevel(const int l, unsigned int seed){
    switch(l){
        case 0:{
            level = make_unique<LevelZero>(file0);
            break;
        }
        case 1:{
            level = make_unique<LevelOne>(seed);
            break;
        }
        case 2:{
            level = make_unique<LevelTwo>(seed);
            break;
        }
        case 3:{
            level = make_unique<LevelThree>(seed);
            break;
        }
        case 4:{
            level = make_unique<LevelFour>(seed);
            break;
        }
    }
}

bool Player::getNextBlock(){
    BlockType type;
    if(restriction == Restriction::forced) type = forcedType;
    else type = nextType;
    currentBlock = board->newBlock(type, 1, 0, level->level);
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    Block::furtherCalculates(MoveType::moveDown, pos, 4);
    for( int i = 0; i < 4; i++){
        if(board->grid[pos[i].first][pos[i].second]){
            success = false;
            return false;
        }
    }
    board->addBlock(currentBlock);
    nextType = level->nextBlock();
    return true;
}

void Player::down(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    if(board->checkPosition(currentBlock,pos)){
        board->eraseBlock(currentBlock);
        currentBlock->down();
        board->addBlock(currentBlock);
        if(level->applyHeavy()) pureDown();
    }
}
void Player::pureDown(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    if(board->checkPosition(currentBlock,pos)){
        board->eraseBlock(currentBlock);
        currentBlock->down();
        board->addBlock(currentBlock);
    }
}
void Player::getHorizontalDowns(unique_ptr<pair<int, int>[]>& pos, int& downs, const int blockSize){
    if(level->applyHeavy()) downs ++;
    if(restriction == Restriction::specialHeavy) downs += 2;
    for( int i = 0; i < downs; i++) Block::furtherCalculates(MoveType::moveDown, pos, blockSize);
}

void Player::left(){
    //Calculate position:
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveLeft);
    int downs = 0;
    getHorizontalDowns(pos, downs,currentBlock->getSize());

    //Move the block if possible, if no space left below, cannot move, must down or drop.
    if(board->checkPosition(currentBlock, pos)){
        board->eraseBlock(currentBlock);
        currentBlock->left();
        for( int i = 0; i < downs; i++) currentBlock->down();
        board->addBlock(currentBlock);
    }
}

void Player::right(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveRight);
    int downs = 0;
    getHorizontalDowns(pos, downs, currentBlock->getSize());

    //Move the block if possible, if no space left below, cannot move, must down or drop.
    if(board->checkPosition(currentBlock,pos)){
        board->eraseBlock(currentBlock);
        currentBlock->right();
        for( int i = 0; i < downs; i++) currentBlock->down();
        board->addBlock(currentBlock);
    }
}

void Player::rotateClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(level->applyHeavy()) Block::furtherCalculates(MoveType::moveDown, pos, currentBlock->getSize());
    if(board->checkPosition(currentBlock, pos)){
        board->eraseBlock(currentBlock);
        currentBlock->Clockwise();
        currentBlock->down();
        board->addBlock(currentBlock);
    } 
}

void Player::rotateCounterClockwise(){
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
    if(level->applyHeavy()) Block::furtherCalculates(MoveType::moveDown, pos, currentBlock->getSize());
    if(board->checkPosition(currentBlock, pos)){
        board->eraseBlock(currentBlock);
        currentBlock->counterClockwise();
        currentBlock->down();
        board->addBlock(currentBlock);
    }
}

void Player::drop(){
    const vector<Cell>& c = currentBlock->getCells();
    int smallestDif = board->gridH - 1;
    int i = 0;
    int difCol = -1;
    for(;i < 4; i++){
        pair<int, int> pos = c[i].getPosition();
        int colLowest = board->checkColBot(pos.second);
        int temp = colLowest - pos.first;
        if(difCol == i){
            if(temp > smallestDif) smallestDif = temp;
        }
        if(temp < smallestDif) {
            difCol = i;
            smallestDif = temp;
        }
    }
    for(int j = 0; j < smallestDif; j++)pureDown();;
    board->checkFilledLines(level.get());
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

void Player::levelUp(){
    if(currentLevel < 4){
        currentLevel++;
        setLevel(currentLevel, seed);
    }else throw "Cannot levelup anymore.";
}

void Player::levelDown(){
    if(currentLevel > 0){
        currentLevel--;
        setLevel(currentLevel, seed);
    }else throw "Cannot leveldown anymore.";
}

int Player::getState()const{
    return success;
}

int Player::getLinesDeleted(){
    return board->getLinesDeleted();
}

bool Player::setBlock(BlockType type){
    board->eraseBlock(currentBlock);
    currentBlock = board->newBlock(type, currentBlock->getCells()[0].getPosition().first, currentBlock->getCells()[0].getPosition().second, 0);
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
}
