#ifndef PLAYER__H
#define PLAYER__H
#include "sprite.h"
#include <vector>
class Player{
public:
  Player(Drawable*, std::vector<Drawable*>);
  ~Player ();
  void moveRight(Uint32);
  void moveLeft(Uint32);
  void attack(int);
  void draw();
  Drawable* getSprite() const {return sprite;} 
  void jump();

private:
  Drawable *sprite, *current;
  bool isAttacking;
  std::vector<Drawable*> attacks;

};
#endif
