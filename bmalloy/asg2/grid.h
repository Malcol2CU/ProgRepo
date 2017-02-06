#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GridSquare{
  public: 
    GridSquare();
    ~GridSquare();
    
    void setPosition(int, int, int);
    void place(const std::string &path, SDL_Renderer *render);
    void render(SDL_Renderer*);
    void contains(int, int);
    
    
  private:
    SDL_Point start_pos;
    SDL_Texture* texture;
    SDL_Rect rect;
	int width;
    bool placed;
    std::string type; 
};
#endif
