#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player(const std::string& walk, const std::string& jump, const std::string& a1,const std::string& death):
  TwoWaySprite(walk),
  initialV(Vector2f(Gamedata::getInstance().getXmlInt(walk+"R/speedX"),
                    Gamedata::getInstance().getXmlInt(walk+"R/speedY")))
  { }

Player::Player(const Player& s) :
  TwoWaySprite(s),
  initialV(s.initialV)
  { }

void Player::processKeyState(const Uint8* keystate, Uint32 ticks){
  if ( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] )  {
  	moveRight();
  	update(ticks);
  }
  else if( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] ){
  	moveLeft();
  	update(ticks);
  }
}

void Player::moveRight(){
std::cout << getVelocityX() << std::endl;
   if(frames != rightFrames) frames = rightFrames;
   setVelocity(initialV);
}

void Player::moveLeft(){
std::cout << -getVelocityX() << std::endl;
   if(frames != leftFrames) frames = leftFrames;
   setVelocity(-initialV);
}
