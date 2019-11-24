#include "player.h"
using namespace std;

Player::Player(string name, Board *board): name{name}, board{new board} {}

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

