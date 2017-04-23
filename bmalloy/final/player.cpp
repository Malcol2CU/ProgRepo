#include "player.h"
#include "gamedata.h"
#include "renderContext.h"
#include <cmath>

Player::Player(const std::string& walk, const std::string& a1, const std::string& death):
  TwoWaySprite(walk),
  initialV(Vector2f(Gamedata::getInstance().getXmlInt(walk+"R/speedX"),
                    Gamedata::getInstance().getXmlInt(walk+"R/speedY"))),
  spinAttack(RenderContext::getInstance()->getFrames(a1)),
  deathFrames(RenderContext::getInstance()->getFrames(death)),
  cycle(false),
  movingRight(true),
  alive(true),
  bulletName("bullet"),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") )
  {frames = rightFrames; }

Player::Player(const Player& s) :
  TwoWaySprite(s),
  initialV(s.initialV),
  spinAttack(s.spinAttack),
  cycle(s.cycle),
  movingRight(s.movingRight),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
  { }

void Player::processKeyState(const Uint8* keystate, Uint32 ticks){
  bullets.update(ticks);
  if(cycle) update(ticks);
  else
  if ( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] )  {
  	moveRight();
  	update(ticks);
  }
  else if( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] ){
  	moveLeft();
  	update(ticks);
  }
  else if(keystate[SDL_SCANCODE_SPACE]) {
        shoot();
        //update(ticks);
  }
}


void Player::moveRight(){
   if(frames != rightFrames) frames = rightFrames;
   movingRight = true;
   setVelocity(initialV);
}

void Player::moveLeft(){
   if(frames != leftFrames) frames = leftFrames;
   movingRight = false;
   setVelocity(-initialV);
}

void Player::attack(int attack){
  if(frames != spinAttack) frames = spinAttack;
  cycle = true;
}

void Player::stop(){
   setVelocity(Vector2f(0.0,0.0));
   cycle = false;
   if(alive){
   if(movingRight) frames = rightFrames;
   else frames = leftFrames;}
}

void Player::die(){
   alive = false;
   frames = deathFrames;
   cycle = true;
}

void Player::shoot() { 
  float x, speed, y = getY()+getFrame()->getHeight()/5;
  // I'm not adding minSpeed to y velocity:
  if(movingRight){ 
	x = getX()+getFrame()->getWidth();
        speed = std::abs(minSpeed+getVelocityX());
  }
  else{
	 x = getX()-getFrame()->getWidth();
	speed = -minSpeed+getVelocityX();
  }

  bullets.shoot( Vector2f(x, y), Vector2f(speed, 0));
}

bool Player::collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}

