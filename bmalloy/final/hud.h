#ifndef HUD_H
#define HUD_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "ioMod.h"

class Hud{
  public:
    Hud();
    ~Hud();
    void draw(int, int, int, int, int, int);
    void display();
  private:
    SDL_Rect hud;
    SDL_Renderer * const renderer;
    const IOmod& io;
    Uint8 alpha;
};

#endif
