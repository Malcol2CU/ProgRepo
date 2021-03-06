#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "gamedata.h"
#include "engine.h"


std::string p[2][3] = {{"walk", "spinAttack", "grimDeath"}, {"billyWalk", "billyGunR", "grimDeath"}};

void Engine::setCharacter(int i){grim = new Player(p[i][0], p[i][1], p[i][2], i); switchSprite(); initSprites();}

class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getScale() < rhs->getScale();
  }
};

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for(auto const& value: sprites) {
	  delete value;
  }
  delete grim;
  delete hud;
  delete strategy;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
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
  deadSprites(),
  grim(new Player(p[0][0], p[0][1], p[0][2], 0)),
  makeVideo( false ),
 frameGen(),
  hud(new Hud()),
  strategy( new PerPixelCollisionStrategy )
{

  grim->setVelocityX(200.0);
  grim->setVelocityY(0.0);
}

void Engine::initSprites(){
  constexpr float u = 1.0f; //Mean size
  constexpr float d = 0.7f; //Std deviation

  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<float> dist(u,d);
  sprites.clear();
  unsigned int n = 50;
  for ( unsigned int i = 0; i < n; ++i ) {
    auto* s = new Enemy("ghost");
    s->makeVelocity(100, 200);
    float scale = dist(mt);
    while(scale < 0.1f) scale = dist(mt);
    s->setScale(scale);
    s->makePosition(500,600);
    sprites.push_back(s);
  }
  std::vector<Enemy*>::iterator ptr = sprites.begin();
  sort(ptr, sprites.end(), SpriteLess());
  std::cout << "Loading complete" << std::endl;
}

void Engine::checkForCollisions() {
   for(int x = 3*(sprites.size()/5); x < static_cast<int>(4*(sprites.size()/5)); x++){ 
         sprites[x]->attack(*grim);
   	 if(grim->collidedWith(sprites[x]) && sprites[x]->isAlive()){
           sprites[x]->die();
	 } 
   	 if(strategy->execute(*grim, *sprites[x]) && sprites[x]->isAlive() && grim->isAlive()){
   	 	if(grim->isAttacking()) sprites[x]->die();
   	 	else grim->dropHealth(); sprites[x]->die();
   	 }   
   } 
}

void Engine::draw() const {
  layer6.draw();
  layer5.draw();
  for(int x = 0; x < static_cast<int>(sprites.size()/5); x++) sprites[x]->draw();
  layer4.draw();
  for(int x = (sprites.size()/5); x < static_cast<int>(2*(sprites.size()/5)); x++) sprites[x]->draw();
  layer3.draw();
  for(int x = 2*(sprites.size()/5); x < static_cast<int>(3*(sprites.size()/5)); x++) sprites[x]->draw();
  layer2.draw();
  for(int x = 2*(sprites.size()/5); x < static_cast<int>(3*(sprites.size()/5)); x++) sprites[x]->draw();
  layer1.draw();
  for(int x = 3*(sprites.size()/5); x < static_cast<int>(4*(sprites.size()/5)); x++) sprites[x]->draw();
  for(auto* s : deadSprites) s->draw();
  grim->draw();
  hud->draw(1, 1, 300,200, clock.getFps(), clock.getSeconds());
  viewport.draw();
  
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
  for(auto* x: deadSprites) x->update(ticks);
  grim->update(ticks);
  layer6.update();
  layer5.update();
  layer4.update();
  layer3.update();
  layer2.update();
  layer1.update();

  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  Viewport::getInstance().setObjectToTrack(grim);
}
bool Engine::play() {

  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  

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
		    if ( keystate[SDL_SCANCODE_F1] ) {
		      hud->display();
		    }
		    if ( keystate[SDL_SCANCODE_E] ) {
  			 for(auto a: sprites) a->explode();
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
   if(grim->isAlive())grim->processKeyState(keystate);
   ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      checkForCollisions();
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
   
  }
return false;
}
