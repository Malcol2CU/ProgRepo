#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaysprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for(auto const& value: sprites) {
	  delete value;
  }
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  layer6("layer6", Gamedata::getInstance().getXmlInt("layer6/factor") ),
  layer5("layer5", Gamedata::getInstance().getXmlInt("layer5/factor") ),
  layer4("layer4", Gamedata::getInstance().getXmlInt("layer4/factor") ),
  layer3("layer3", Gamedata::getInstance().getXmlInt("layer3/factor") ),
  layer2("layer2", Gamedata::getInstance().getXmlInt("layer2/factor") ),
  layer1("layer1", Gamedata::getInstance().getXmlInt("layer1/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  currentSprite(-1),

  makeVideo( false )
{
  sprites.push_back( new TwoWaySprite("runR", "runL") );
  sprites.push_back(new MultiSprite("rock"));
  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  layer6.draw();
  layer5.draw();
  layer4.draw();
  layer3.draw();
  layer2.draw();
  layer1.draw();
  
  SDL_Color color = {255, 50, 50, 255};
  
  io.writeText(Gamedata::getInstance().getXmlStr("username"),
	Gamedata::getInstance().getXmlFloat("view/width")/2.4,0, color);
	
  std::stringstream strm;
  strm << "fps: " << clock.getFps() << " Avg FPS:" << clock.getAvgFps();
  io.writeText(strm.str(), 30, 60);


  for(auto* s : sprites) s->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

bool Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  layer6.update();
  layer5.update();
  layer4.update();
  layer3.update();
  layer2.update();
  layer1.update();
  viewport.update(); // always update viewport last
  if (sprites[0]->getX() == sprites[1]->getX() || sprites[0]->getY() == sprites[1]->getY())
	return true;
  return false;
}

void Engine::switchSprite(){
  currentSprite = ++currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_S] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      done = update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
