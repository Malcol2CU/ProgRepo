#include "player.h"
#include "sprite.h"

Player::Player(Drawable* d, std::vector<Drawable*> a): sprite(d), current(nullptr), isAttacking(false), attacks(a){
}


void Player::draw(){
	 sprite->draw();
}

void Player::moveRight(Uint32 ticks){
    sprite->moveRight(ticks);
}
void Player::moveLeft(Uint32 ticks){
    sprite->moveLeft(ticks);
}
  
void Player::attack(int attackNum){
}
	
void Player::jump(){
  
}
