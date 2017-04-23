#ifndef ENEMY__H
#define ENEMY__H
#include <string>
#include "twowaysprite.h"
#include "player.h"

class Enemy : public TwoWaySprite {
  public:
	Enemy(const std::string& name);
	Enemy(const Enemy&);
        bool isAlive(){return alive;}
	void attack(Player& d);
        void die(){ 
  		alive = false;
		explode();       
 	}

  private:
  std::vector<Frame *> attackR, attackL;
  bool alive;

};
#endif
