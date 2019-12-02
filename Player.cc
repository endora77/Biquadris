#include "Player.h"
using namespace std;
Player::Player(std::string name, const int lev, std::vector<std::unique_ptr<Observer>>& displays,
       const int height, const int width, int seed, const std::string file0):
name{name}, file0 {file0}, restriction{Restriction::noRestriction},playing{false}{
    for(auto& a : displays){
        attach(a.get());
    }
    setLevel(lev, seed);
    currentLevel = lev;
    board = std::make_unique<Board>(height, width);
    this->seed = seed;
    success = true;
    nextType = level->nextBlock();
}
bool Player::norand(const std::string file){
    return level->unsetRandom(file);
}
bool Player::rand(){
    return level->setRandom();
}
//Throws an error
void Player::setLevel(const int l, unsigned int seed){
    switch(l){
        case 0:{
            if(!(file0 == "no_file_specified" || file0 == "")){
                level = make_unique<LevelZero>(file0);
                break;
            }else{
                throw "Error: No sequence file for level zero.";
            }
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
    currentBlock->down();
    currentBlock->down();
    board->addBlock(currentBlock);
    nextType = level->nextBlock();
    return true;
}

void Player::down(const int times){
    for(int i = 0; i < times; i++){
        unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
        if(board->checkPosition(currentBlock,pos)){
            board->eraseBlock(currentBlock);
            currentBlock->down();
            board->addBlock(currentBlock);
        }
    }
}

void Player::getHorizontalDowns(unique_ptr<pair<int, int>[]>& pos, int& downs, const int blockSize){
    if(level->applyHeavy()) downs ++;
    if(restriction == Restriction::specialHeavy) downs += 2;
    for( int i = 0; i < downs; i++) Block::furtherCalculates(MoveType::moveDown, pos, blockSize);
}

void Player::left(const int times){
    bool moved = false;
    for(int i = 0; i < times; i++){
        //Calculate position:
        unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveLeft);
        //int downs = 0;
        //getHorizontalDowns(pos, downs,currentBlock->getSize());
        //Move the block if possible, if no space left below, cannot move, must down or drop.
        if(board->checkPosition(currentBlock, pos)){
            moved = true;
            board->eraseBlock(currentBlock);
            currentBlock->left();
            board->addBlock(currentBlock);
        }
    }
    if(moved){
        int downs = 0;
        if(level->applyHeavy()) downs ++;
        if(restriction == Restriction::specialHeavy) downs += 2;
        down(downs);
    }
}

void Player::right(const int times){
    bool moved = false;
    for(int i = 0; i < times; i++){
        unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveRight);
        //int downs = 0;
        //getHorizontalDowns(pos, downs, currentBlock->getSize());
        if(board->checkPosition(currentBlock,pos)){
            moved = true;
            board->eraseBlock(currentBlock);
            currentBlock->right();
            board->addBlock(currentBlock);
        }
    }
    if(moved){
        int downs = 0;
        if(level->applyHeavy()) downs ++;
        if(restriction == Restriction::specialHeavy) downs += 2;
        down(downs);
    }
}

void Player::rotateClockwise(const int times){
    bool moved = false;
    for(int i = 0; i < times; i++){
        unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
        //if(level->applyHeavy()) Block::furtherCalculates(MoveType::moveDown, pos, currentBlock->getSize());
        if(board->checkPosition(currentBlock, pos)){
            moved = true;
            board->eraseBlock(currentBlock);
            currentBlock->Clockwise();
            board->addBlock(currentBlock);
        }
    }
    if(moved && level->applyHeavy())down(1);
}

void Player::rotateCounterClockwise(const int times){
    bool moved = false;
    for(int i = 0; i < times; i++){
        unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveClockwise);
        //if(level->applyHeavy()) Block::furtherCalculates(MoveType::moveDown, pos, currentBlock->getSize());
        if(board->checkPosition(currentBlock, pos)){
            moved = true;
            board->eraseBlock(currentBlock);
            currentBlock->counterClockwise();
            board->addBlock(currentBlock);
        }
    }
    if(moved && level->applyHeavy())down(1);
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
    down(smallestDif);
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

int Player::getLinesDeleted() const{
    return board->getLinesDeleted();
}

bool Player::setBlock(BlockType type){
    board->eraseBlock(currentBlock);
    Block* lastBlock = currentBlock;
    currentBlock = board->newBlock(type, lastBlock->getCells()[0].getPosition().first, lastBlock->getCells()[0].getPosition().second, level->level);
    unique_ptr<pair<int, int>[]> pos = currentBlock->calcPosition(MoveType::moveDown);
    if(!board->checkPosition(currentBlock, pos)){
        currentBlock = lastBlock;
        board->addBlock(lastBlock);
        return false;
    }else{
        board->addBlock(currentBlock);
        board->currentBlock = currentBlock;
        return true;
    }
}
