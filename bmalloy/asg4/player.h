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

	void moveLeft();
	void moveRight();
	void jump(std::string, std::string);
	void attack(std::string);
        void stop();
  
  private:
	std::vector<Frame *> jumpRight, jumpLeft, attack1;
        bool cycle;

};
#endif
