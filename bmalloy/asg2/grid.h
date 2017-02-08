#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GridSquare{
  public: 
    GridSquare();
    GridSquare(const std::string&, SDL_Renderer*);
    ~GridSquare(){free();}
    
    bool operator==(const GridSquare& square);
    
    void setPosition(int, int);
    void loadTexture(const std::string&, SDL_Renderer*);
    void setTextureDimensions(int, int);
    void render(SDL_Renderer*, int, int);
    void contains(int, int);
    bool notEmpty() const{ return placed;}
    void free();
    
  private:
    SDL_Texture* texture;
    SDL_Rect rect;
    bool placed;
    std::string type; 
};
#endif
