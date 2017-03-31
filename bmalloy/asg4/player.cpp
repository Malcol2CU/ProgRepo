#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

Player::Player(const std::string& walk, const std::string& jump, const std::string& a1):
  TwoWaySprite(walk),
  jumpRight(RenderContext::getInstance()->getFrames(jump+"R")),
  jumpLeft( RenderContext::getInstance()->getFrames(jump+"L")),
  attack1(RenderContext::getInstance()->getFrames(a1)),
  cycle(false)
{ std::cout<< "player created" << std::endl;}

Player::Player(const Player& s) :
  TwoWaySprite(s)
  { }

void Player::update(Uint32 ticks) { 
  if(currentFrame == numberOfFrames-1){ 
    cycle = false; currentFrame = 0;
  }
  if(cycle){
    advanceFrame(ticks);
    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);
  }
}

void Player::moveRight(){
   frames = rightFrames;
   cycle = true; 
}

//void Player::moveRight(std::string s){
  //cycle = true;
  //if(current != s){
    //foward = true;
    //current = s;
    //setVelocityX( fabs( getVelocityX() ) );
    //switchFrames(s);
  //}
//}

//void Player::jump(std::string fowardJ, std::string j){
  //cycle = true;
  //if(foward) switchFrames(fowardJ);
  //else switchFrames(j);
//}

//void Player::attack(std::string s){
  //cycle =  true;
  //switchFrames(s);
//}

//void Player::switchFrames(std::string framewalk){
    //frames = RenderContext::getInstance()->getFrames(framewalk);
    //numberOfFrames = Gamedata::getInstance().getXmlInt(framewalk+"/frames"); 
    //frameInterval = Gamedata::getInstance().getXmlInt(framewalk+"/frameInterval");
    //currentFrame = 0;
//}


