#ifndef HUD_H
#define HUD_H
#include <SDL.h>
#include <iostream>
#include <string>
#include "gamedata.h"
#include "renderContext.h"

Class Hud{
  public:
    Hud();
    ~Hud();
    void update();
    void draw();

  private:
    SDL_Rect hud
};

Hud::Hud():hud(0,0,300,300){
	SDL_RenderCopy(renderContext::getInstance().getRenderer(), NULL, NULL, &hud);
}
#endif
