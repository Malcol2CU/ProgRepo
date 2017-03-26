#include "player.h"
#include "sprite.h"

Player::Player(Drawable* d): sprite(d){
  }

void Player::moveRight(Uint32 ticks){
    sprite->moveRight(ticks);
  }
void Player::moveLeft(Uint32 ticks){
    sprite->moveLeft(ticks);
  }
void Player::jump(){
  
  }
