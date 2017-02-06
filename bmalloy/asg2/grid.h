#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GridSquare{
  public: 
    GridSquare();
    
    void setPosition(int x, int y);
    
    
    
  private:
    SDL_Point position;
};
#endif
