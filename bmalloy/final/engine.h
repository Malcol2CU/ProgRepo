#include <vector>
#include <SDL.h>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "frameGenerator.h"
#include "player.h"
#include "enemy.h"
#include "hud.h"

class CollisionStrategy;

class Engine {
public:
  Engine();
  ~Engine();
  bool play();
  void switchSprite();
void setCharacter(int i);
void makeFrame(){frameGen.makeFrame();}
private:
  const RenderContext* rc;
  Clock& clock;
  SDL_Renderer * const renderer;
  
  World layer6;
  World layer5;
  World layer4;
  World layer3;
  World layer2;
  World layer1;
  
  Viewport& viewport;

  std::vector<Enemy*> sprites, deadSprites;
  Player* grim; 
  
  bool makeVideo;
FrameGenerator frameGen;
  void draw() const;
  void update(Uint32);
  void initSprites();
  Hud* hud;
  CollisionStrategy* strategy;
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
  void checkForCollisions();
};
