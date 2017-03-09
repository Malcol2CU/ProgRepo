#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
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

  int currentSprite;
  bool makeVideo;

  void draw() const;
  bool update(Uint32);

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
};
