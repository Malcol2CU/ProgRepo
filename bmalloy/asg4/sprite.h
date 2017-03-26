#ifndef SPRITE__H
#define SPRITE__H
#include <string>
#include "drawable.h"

class Sprite : public Drawable {
public:
  Sprite(const std::string&);
  Sprite(const Sprite&);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual int getHeight() const {return frameHeight;}
  virtual int getF() const { return 0;}
  virtual void moveLeft(Uint32 ticks){std::cout << ticks;}
  virtual void moveRight(Uint32 ticks){std::cout << ticks;}
private:
  const Frame * frame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  int getDistance(const Sprite*) const;
};
#endif
