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
  


protected:
  std::vector<Frame *> rightFrames, leftFrames;

  TwoWaySprite& operator=(const TwoWaySprite&) = delete;
};
#endif
