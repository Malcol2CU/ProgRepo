#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class GridSquare{
  public: 
    //Contructors and Deconstructor
    GridSquare();
    GridSquare(const std::string&, SDL_Renderer*, const char);
    ~GridSquare(){free();}
    
    //Functions
    void setPosition(int, int);
    void loadTexture(const std::string&, SDL_Renderer*, const char);
    void setTextureDimensions(int, int);
    void render(SDL_Renderer*, int, int);
    bool notEmpty() const{ return placed;}
    char getType() const{ return type;}
    void free();
    void init(){GridSquare();}
    
    //Overloaded Operators:
    bool operator==(const GridSquare& square);
    
    //Deleted Constructs and Operators
    GridSquare(const GridSquare&) = delete;
    GridSquare operator=(const GridSquare&) = delete;
    
  private:
    SDL_Texture* texture;
    SDL_Rect rect;
    bool placed;
    char type; 
};
#endif
