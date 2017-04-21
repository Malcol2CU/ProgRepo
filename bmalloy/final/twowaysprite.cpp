#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"

TwoWaySprite::TwoWaySprite( const std::string& name) :
  MultiSprite(name),
  rightFrames(frames),
  leftFrames(RenderContext::getInstance()->getFrames(name+"/move/moveL/")),
  alive(true)
  { if(getVelocityX() < 0.0) frames = leftFrames; }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  MultiSprite(s), 
  rightFrames(s.rightFrames),
  leftFrames(s.leftFrames),
  alive(true)
  { if(getVelocityX() < 0.0) frames = leftFrames; }
  
void TwoWaySprite::update(Uint32 ticks) { 
   if ( getX() < 0) {
	frames = rightFrames;
   }
	
   if ( getX() > worldWidth-scale*frameWidth) {
	frames = leftFrames;
   }  
   MultiSprite::update(ticks);
}
