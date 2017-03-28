#include "player.h"
#include "gamedata.h"
#include "renderContext.h"

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

Player::Player(std::string name):
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  current(name),
  currentFrame(0),
  
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  cycle(false),
  foward(true)
{ std::cout<< "class created" << std::endl;}

Player::Player(const Player& s) :
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
  cycle(false),
  foward(true)
  { }

void Player::draw() const { 
  frames[currentFrame]->draw(getX(), getY());
}

void Player::update(Uint32 ticks) { 
  if(currentFrame != numberOfFrames-1 && cycle){ 
  	advanceFrame(ticks);
  	Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  	setPosition(getPosition() + incr);
  }
  else{ 
  	cycle = false;
  	switchFrames(current);
  }
}

void Player::moveLeft(std::string s){
 cycle = true;
  if(current != s){
    foward = false;
    current = s;
    setVelocityX( -fabs( getVelocityX() ) );
    switchFrames(s);
    }
}

void Player::moveRight(std::string s){
  cycle = true;
  if(current != s){
    foward = true;
    current = s;
    setVelocityX( fabs( getVelocityX() ) );
    switchFrames(s);
  }
}

void Player::jump(std::string fowardJ, std::string j){
  cycle = true;
  if(foward) switchFrames(fowardJ);
  else switchFrames(j);
}

void Player::attack(std::string s){
  cycle =  true;
  switchFrames(s);
}

void Player::switchFrames(std::string frameName){
    frames = RenderContext::getInstance()->getFrames(frameName);
    numberOfFrames = Gamedata::getInstance().getXmlInt(frameName+"/frames"); 
    frameInterval = Gamedata::getInstance().getXmlInt(frameName+"/frameInterval");
    currentFrame = 0;
}


