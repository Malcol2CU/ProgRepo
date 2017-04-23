#include "enemy.h"
#include "gamedata.h"
#include "renderContext.h"
#include <cmath>

Enemy::Enemy(const std::string& name):
  TwoWaySprite(name),
  attackR(RenderContext::getInstance()->getFrames("attackR")),
  attackL(RenderContext::getInstance()->getFrames("attackL")),
  alive(true)
  { }

Enemy::Enemy(const Enemy& s) :
  TwoWaySprite(s),
  attackR(s.attackR),
  attackL(s.attackL),
  alive(s.alive)
  { }



void Enemy::attack(Player& d){
  bool a = false;

  float left = d.getX();
  float scale = d.getScale();
  float right = left+scale*d.getFrame()->getWidth();
  float top = d.getY();
  float bottom = top+scale*d.getFrame()->getHeight();

  float myRight = getX()+getScale()*getFrame()->getWidth();
  float mybottom = getY()+getScale()*getFrame()->getHeight();

  if(std::abs(left - getX()) < 100 && std::abs(bottom-getY()) < 200 && alive) a = true;
  else if(std::abs(right - myRight) < 100 && std::abs(bottom-getY()) < 200 && alive) a = true;
  else a = false;
  if(a && frames == rightFrames && d.isAlive()) frames = attackR;
  if(a && frames == leftFrames && d.isAlive()) frames = attackL;
  if(!a && getVelocityX() > 0.0){ frames = rightFrames; currentFrame = 0;}
  if(!a && getVelocityX() < 0.0) {frames = leftFrames;  currentFrame = 0;}

}

