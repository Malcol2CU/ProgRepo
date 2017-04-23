#include "multisprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "renderContext.h"

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  scale(1),
  isExploding(false),
  explodeSprite(new Sprite(name))
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
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
  scale(1),
  isExploding(false),
  explodeSprite(s.explodeSprite)
  { }

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void MultiSprite::draw() const { 
  if(isExploding) explodeSprite -> draw();
  else{
	if(getScale() < SCALE_EPSILON) return;
	frames[currentFrame]->draw(getX(), getY(), scale); 
  }
}

void MultiSprite::update(Uint32 ticks) { 
   if(isExploding) explodeSprite -> update(ticks);
   else{
	advanceFrame(ticks);
	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
	setPosition(getPosition() + incr);

	if ( getY() < 0)  
	   setVelocityY(fabs(getVelocityY()));
	
	if (getY() > worldHeight-scale*frameHeight) 
	   setVelocityY(-fabs(getVelocityY()));
	
	if ( getX() < 0) {
	  setVelocityX( fabs( getVelocityX() ) );
	}
	
	if ( getX() > worldWidth-scale*frameWidth) {
	  setVelocityX( -fabs( getVelocityX() ) );
	}  
   }
}
void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void MultiSprite::explode(){
  isExploding = true;
  explodeSprite->setFrame(frames[currentFrame]);
  explodeSprite->setY(getY());
  explodeSprite->setX(getX());
  Drawable* boom = 
  new ExplodingSprite(*static_cast<Sprite*>(explodeSprite));
  delete explodeSprite;
  explodeSprite = boom;
}

Vector2f MultiSprite::makeVelocity(int vx, int vy) const {
  float newvx = Gamedata::getInstance().getRandFloat(vx-50,vx+50);;
  float newvy = Gamedata::getInstance().getRandFloat(vy-50,vy+50);;
  newvx *= [](){ if(rand()%2) return -1; else return 1; }();
  newvy *= [](){ if(rand()%2) return -1; else return 1; }();

  return Vector2f(newvx, newvy);
}

void MultiSprite::makePosition(int vx, int vy) {
  float newvx = Gamedata::getInstance().getRandInRange(vx-300,vx+300);
  float newvy = Gamedata::getInstance().getRandInRange(vy-200,vy+50);

  const Vector2f vec(newvy, newvx);
  setPosition(vec);
}
