#ifndef PLAYER__H
#define PLAYER__H
#include "sprite.h"
class Player{
public:
  Player(Drawable* d);
  ~Player ();
  void moveRight(Uint32 ticks);
  void moveLeft(Uint32 ticks);
  void attack(int attackNum);
  void addAttack(Drawable *);
  void draw(){ sprite->draw();}
  Drawable* getSprite() const {return sprite;} 
  void jump();

private:
  Drawable *sprite;
  std::vector<Drawable*> attacks;

};
#endif
