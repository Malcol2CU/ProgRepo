#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite( const std::string&);
  TwoWaySprite(const TwoWaySprite&);

  virtual void draw() const;
  virtual void update(Uint32);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  
  inline float getScale()const{ return scale; }
  void  setScale(float s){ scale = s; }
  Vector2f makeVelocity(int, int) const;
  void makePosition(int, int);

protected:
  std::vector<Frame *> frames, rightFrames, leftFrames;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  void advanceFrame(Uint32 ticks);
  float scale;
  int getDistance(const TwoWaySprite*) const;
  int makeRandom();
};
#endif
