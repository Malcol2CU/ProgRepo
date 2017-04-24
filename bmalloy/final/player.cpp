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
  movingRight(true),
  alive(true),
  bulletName("bullet"),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  health(1.0)
  {frames = rightFrames; currentFrame = numberOfFrames-1; }

Player::Player(const Player& s) :
  TwoWaySprite(s),
  initialV(s.initialV),
  spinAttack(s.spinAttack),
  movingRight(s.movingRight),
  bullets(s.bullets),
  minSpeed(s.minSpeed)
  { }

void Player::processKeyState(const Uint8* keystate, Uint32 ticks){
  if ( keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT] )  {
  	moveRight();
  }
  else if( keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT] ){
  	moveLeft();
  }
  else if(keystate[SDL_SCANCODE_SPACE]) {
        shoot();
  }
  else if(keystate[SDL_SCANCODE_Z]) {
	if (currentFrame == numberOfFrames-1) currentFrame =0;
        attack(1);
  }
}


void Player::moveRight(){
   if(frames != rightFrames) frames = rightFrames; currentFrame = 0;
   movingRight = true;
   setVelocity(initialV);
}

void Player::moveLeft(){
   if(frames != leftFrames) frames = leftFrames; currentFrame = 0;
   movingRight = false;
   setVelocity(-initialV);
}

void Player::attack(int attack){
  if(frames != spinAttack) frames = spinAttack;
}

void Player::stop(){
   setVelocity(Vector2f(0.0,0.0));
   if(alive){
      if(movingRight) frames = rightFrames;
      else frames = leftFrames;
   }
}

void Player::die(){
   alive = false;
   frames = deathFrames;
}

void Player::shoot() { 
  float x, speed, y = getY()+getFrame()->getHeight()/5;

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

void Player::RenderHPBar(int x, int y, int w, int h, float Percent) const {
   SDL_Renderer * Renderer = RenderContext::getInstance()->getRenderer();  
   Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;

   SDL_Rect bgrect = { x, y, w, h };
   SDL_SetRenderDrawColor(Renderer, 100,100,100,255);
   SDL_RenderFillRect(Renderer, &bgrect);
   SDL_SetRenderDrawColor(Renderer, 50,50,50,255);
   SDL_RenderDrawRect(Renderer, &bgrect);
   int pw = (int)((float)w * Percent);
   int px = x + (w - pw);
   SDL_Rect fgrect = { px, y, pw, h };
   SDL_RenderFillRect(Renderer, &fgrect);
   SDL_SetRenderDrawColor(Renderer, 255, 90, 90, 255);
   SDL_RenderDrawRect(Renderer, &fgrect);
}

