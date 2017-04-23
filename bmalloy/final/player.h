#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include "twowaysprite.h"
#include "bulletPool.h"

class Player : public TwoWaySprite {
public:
   Player(const std::string&, const std::string&, const std::string&);
   Player(const Player&);

   virtual void update(Uint32 ticks){
      TwoWaySprite::update(ticks); 
      if(currentFrame == numberOfFrames-1 && cycle) stop();	
   }
   virtual void draw() const{
      TwoWaySprite::draw();
      bullets.draw();
   }
   virtual bool collidedWith(const Drawable*) const;
   
   bool isAlive(){return alive;}
   bool isAttacking(){ return cycle;}
   void processKeyState(const Uint8* keystate, Uint32 ticks );
   void shoot();
   void die();

private:
   Vector2f initialV;
   std::vector<Frame *> spinAttack, deathFrames;
   bool cycle, movingRight, alive;	
   std::string bulletName;
   BulletPool bullets;
   float minSpeed;

   void moveLeft();
   void moveRight();
   void attack(int attack);
   void stop();

   Player& operator=(const Player&) = delete;
};
#endif
