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

void Player::processKeyState(const Uint8* keystate){
    if ( keystate[SDL_SCANCODE_SPACE] ) {
    	attack();
		setVelocityX(0.0);
        if ( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] )  setVelocityX(200.0);
        else if( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] ) setVelocityX(-200.0);
    }
    else if ( keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]  ) {
    	jump();
    }
    else if ( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] ) {
		moveRight();
    }
    else if ( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] ) {
    	moveLeft();
    }
}

void Player::moveRight(){
   frames = current = rightFrames;
   setVelocityX(200);
   cycle = true; 
}

void Player::moveLeft(){
   frames = current = leftFrames;
   setVelocityX(-200);
   cycle = true; 
}

void Player::jump(){
  if(current == rightFrames) frames = jumpRight;
  else frames = jumpLeft;
  setVelocityX(0.0);
  cycle = true;
}

void Player::attack(){
  frames = attack1;
  cycle =  true;
}
