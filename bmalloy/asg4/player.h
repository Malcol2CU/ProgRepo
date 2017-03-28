#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class Player: public Drawable{
public:
  Player(std::string);
  Player(const Player&);
  
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual int getHeight() const {return frameHeight;}
  virtual int getF() const { return currentFrame;}
  
  void moveLeft(std::string);
  void moveRight(std::string);
  void jump(std::string, std::string);
  void attack(std::string);
  
private:
  std::vector<Frame *> frames;
  std::string current;
  
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  bool cycle, foward;
  void advanceFrame(Uint32 ticks);
  void switchFrames(std::string);

};
#endif
