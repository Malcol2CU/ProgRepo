#include "twowaysprite.h"
#include "gamedata.h"
#include "renderContext.h"

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWaySprite::TwoWaySprite( const std::string& name) :
  Drawable(name+"R", 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"R/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"R/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"R/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"R/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name+"R") ),
  rightFrames(frames),
  leftFrames(RenderContext::getInstance()->getFrames(name+"L")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"R/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"R/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  frames(s.frames),
  rightFrames(s.rightFrames),
  leftFrames(s.leftFrames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }

void TwoWaySprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY());
}

void TwoWaySprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    frames = rightFrames;
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
    frames = leftFrames;
  }  
}
