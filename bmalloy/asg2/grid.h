#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Grid{
  public: 
    static Grid& getInstance(std::string path){
      if(instance == NULL) instance = new Grid(path);
      return instance;
    }
    
    Grid(const Grid&) = delete;
    Grid() = delete;
    void operator=(const Grid&) = delete;
  private:
    static Grid instance;
    Grid(std::string);
};
#endif
