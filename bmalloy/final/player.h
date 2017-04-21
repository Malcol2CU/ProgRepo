#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include "twowaysprite.h"

class Player : public TwoWaySprite {
  public:
	Player(const std::string&, const std::string&, const std::string&, const std::string&);
	Player(const Player&);
	
	void processKeyState(const Uint8* keystate, Uint32 ticks );

  
  private:
	Vector2f initialV;
	
	void moveLeft();
	void moveRight();
};
#endif
