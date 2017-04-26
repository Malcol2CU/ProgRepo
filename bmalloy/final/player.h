#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include "twowaysprite.h"
#include "bulletPool.h"


class Player : public TwoWaySprite {
public:
   Player(const std::string&, const std::string&, const std::string&, int);
   Player(const Player&);

   virtual void update(Uint32 ticks){ 
      bullets.update(ticks);
      TwoWaySprite::update(ticks);
      stop();
   }
   virtual void draw() const{
      RenderHPBar(600, 1, -300,20, health);
      TwoWaySprite::draw();
      bullets.draw();
   }
   virtual bool collidedWith(const Drawable*) const;
   
   void dropHealth(){health -= .25; if (health == 0.0) die();}
   bool isAlive(){return alive;}
   bool isAttacking(){ return attacking;}
   void processKeyState(const Uint8* keystate);


private:
   Vector2f initialV;
   std::vector<Frame *> pAttack, deathFrames;

   bool movingRight, alive, attacking;	
   std::string bulletName;
   BulletPool bullets;
   float minSpeed, health;
   int who;
   
   void RenderHPBar(int x, int y, int w, int h, float Percent) const;
   void moveLeft();
   void moveRight();
   void attack(int attack);
   void shoot();
   void die();
   void setNumFrames(){numberOfFrames = frames.size();}
   void stop();

   Player& operator=(const Player&) = delete;
};
#endif
