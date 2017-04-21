#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player(const std::string& walk, const std::string& jump, const std::string& a1,const std::string& death):
  TwoWaySprite(walk),
  jumpRight(RenderContext::getInstance()->getFrames(jump+"R")),
  jumpLeft( RenderContext::getInstance()->getFrames(jump+"L")),
  attack1(RenderContext::getInstance()->getFrames(a1)),
  death(RenderContext::getInstance()->getFrames(death)),
  current(frames),
  cycle(false),
  attacking(false),
  alive(true),
  initVelocity(getVelocityX()),
  bulletName("bullet"),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") )
{ std::cout<< "player created" << std::endl;}

Player::Player(const Player& s) :
  TwoWaySprite(s),
  jumpRight(s.jumpRight),
  jumpLeft( s.jumpLeft),
  attack1(s.attack1),
  death(s.death),
  current(s.current),
  cycle(false),
  attacking(false),
  alive(true),
  initVelocity(getVelocityX()),
  bulletName("bullet"),
  bullets( s.bullets ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") )
  { }

void Player::update(Uint32 ticks) { 
  bullets.update(ticks);
  if(currentFrame == numberOfFrames-1 && alive){ 
    cycle = attacking = false; currentFrame = 0; frames = current; 
    setVelocityX(initVelocity); setVelocityY(0.0);
  }
  else if(currentFrame == numberOfFrames-1) cycle = false;
  if(cycle){
    advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
  }
}
bool Player::isAttacking(){
    if(attacking) return true;
    else return false;
}

void Player::draw() const { 
  TwoWaySprite::draw();
  bullets.draw();
}

void Player::die(){
   frames = current = death;
   setVelocityX(0.0);
   cycle = true; 
   alive = false;
}

void Player::processKeyState(const Uint8* keystate){
    if ( keystate[SDL_SCANCODE_SPACE] ) {
    	shoot();
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
  attacking = true;
  cycle =  true;
}

void Player::shoot() { 
  float x = getX()+getFrame()->getWidth();
  float y = getY()+getFrame()->getHeight()/6;
  // I'm not adding minSpeed to y velocity:
  bullets.shoot( Vector2f(x, y), 
    Vector2f(minSpeed+getVelocityX(), 0)
  );
}

bool Player::collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}
