#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class MultiSprite : public Drawable {
public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  
  inline float getScale()const{ return scale; }
  void  setScale(float s){ scale = s; }
  Vector2f makeVelocity(int, int) const;
  void makePosition(int, int);

  void explode();
protected:
  std::vector<Frame *> frames;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  float scale;
  bool isExploding;
  Drawable* explodeSprite;

  void advanceFrame(Uint32 ticks);
  
  MultiSprite& operator=(const MultiSprite&) = delete;
};
#endif
