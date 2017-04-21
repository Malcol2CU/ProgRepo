#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "multisprite.h"

class TwoWaySprite : public MultiSprite {
public:
  TwoWaySprite( const std::string&);
  TwoWaySprite(const TwoWaySprite&);
 
  virtual ~TwoWaySprite(){}
  virtual void update(Uint32);
  
  bool isAlive(){return alive;}

protected:
  std::vector<Frame *> rightFrames, leftFrames;
  bool alive;

  TwoWaySprite& operator=(const TwoWaySprite&) = delete;
};
#endif
