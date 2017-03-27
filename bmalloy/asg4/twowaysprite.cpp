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

TwoWaySprite::TwoWaySprite( const std::string& name, const std::string& name2) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  rframes(name),
  lframes(name2),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  foward(true)
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  frames(s.frames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  foward(true)
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
    frames = RenderContext::getInstance()->getFrames(rframes);
    numberOfFrames = Gamedata::getInstance().getXmlInt(rframes+"/frames"); 
    frameInterval = Gamedata::getInstance().getXmlInt(rframes+"/frameInterval");
    currentFrame = 0;
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
    frames = RenderContext::getInstance()->getFrames(lframes);
    numberOfFrames = Gamedata::getInstance().getXmlInt(lframes+"/frames"); 
    frameInterval = Gamedata::getInstance().getXmlInt(lframes+"/frameInterval");
    currentFrame = 0;
  }  
}

void TwoWaySprite::moveLeft(Uint32 ticks){
  advanceFrame(ticks);
  std::cout << ticks << std::endl;
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if(foward){
    setVelocityX( -fabs( getVelocityX() ) );
    frames = RenderContext::getInstance()->getFrames(lframes);
    numberOfFrames = Gamedata::getInstance().getXmlInt(lframes+"/frames"); 
    frameInterval = Gamedata::getInstance().getXmlInt(lframes+"/frameInterval");
    currentFrame = 0;
    foward = false;
    }
  }
void TwoWaySprite::moveRight(Uint32 ticks){
  advanceFrame(ticks);
  std::cout << ticks << std::endl;
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if(!foward){
    setVelocityX( fabs( getVelocityX() ) );
    frames = RenderContext::getInstance()->getFrames(rframes);
    numberOfFrames = Gamedata::getInstance().getXmlInt(rframes+"/frames"); 
    frameInterval = Gamedata::getInstance().getXmlInt(rframes+"/frameInterval");
    currentFrame = 0;
    foward = true;
    }
  }
