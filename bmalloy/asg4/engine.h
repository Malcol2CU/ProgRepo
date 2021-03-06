#include <vector>
#include <SDL.h>
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "frameGenerator.h"
#include "player.h"
#include "hud.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

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

  std::vector<Drawable*> sprites;
  Player* grim;  
  
  bool makeVideo;

  void draw() const;
  void update(Uint32);
  Hud* hud;

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
};
