#include <iostream>
#include "multisprite.h"
#include "gamedata.h"

class Bullet : public MultiSprite {
public:
  explicit Bullet(const string& name) :
    MultiSprite(name), 
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
    tooFar(false) 
  { setVelocity(Vector2f(200,0));}
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }

private:
  float distance;
  float maxDistance;
  bool tooFar;
};
