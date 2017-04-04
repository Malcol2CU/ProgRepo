#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "twowaysprite.h"

class Player : public TwoWaySprite {
  public:
	Player(const std::string&, const std::string&, const std::string&);
	Player(const Player&);

	virtual void update(Uint32 ticks);
    void processKeyState(const Uint8* keystate);

	void moveLeft();
	void moveRight();
	void jump();
	void attack();
    void stop();
  
  private:
	std::vector<Frame *> jumpRight, jumpLeft, attack1, current;
        bool cycle;
	float initVelocity;
};
#endif
