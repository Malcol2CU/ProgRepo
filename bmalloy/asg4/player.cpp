#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player(const std::string& walk, const std::string& jump, const std::string& a1):
  TwoWaySprite(walk),
  jumpRight(RenderContext::getInstance()->getFrames(jump+"R")),
  jumpLeft( RenderContext::getInstance()->getFrames(jump+"L")),
  attack1(RenderContext::getInstance()->getFrames(a1)),
  current(frames),
  cycle(false),
  initVelocity(getVelocityX())
{ std::cout<< "player created" << std::endl;}

Player::Player(const Player& s) :
  TwoWaySprite(s)
  { }

void Player::update(Uint32 ticks) { 
  if(currentFrame == numberOfFrames-1){ 
    cycle = false; currentFrame = 0; frames = current; 
    setVelocityX(initVelocity); setVelocityY(0.0);

  }
  if(cycle){
    advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
  }
}

void Player::moveRight(){
   frames = current = rightFrames;
   setVelocityX( fabs( getVelocityX() ) );
   cycle = true; 
}

void Player::moveLeft(){
   frames = current = leftFrames;
   setVelocityX( -fabs( getVelocityX() ) );
   cycle = true; 
}

void Player::jump(){
  if(frames == rightFrames || getVelocityX() > 0) frames = jumpRight;
  else frames = jumpLeft;
  setVelocityX(0.0);
  cycle = true;
}

void Player::attack(){
  frames = attack1;
  setVelocityX(0.0);
  cycle =  true;
}
