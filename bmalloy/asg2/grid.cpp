#include "grid.h"

GridSquare::GridSquare(): placed(false){
    texture = NULL;
}    

GridSquare::GridSquare(const std::string& path, SDL_Renderer* render): placed(false){
      texture = NULL;
      loadTexture(path, render); 
}

void GridSquare::setTextureDimensions(int width, int height){
  rect.w = width;
  rect.h = height;
}

void GridSquare::loadTexture(const std::string &path, SDL_Renderer *render){
  if(texture != NULL) free();
  
  texture = IMG_LoadTexture(render, path.c_str());
  if ( texture == NULL ){std::cout << "error" << std::endl;}	
  placed = true;
}

void GridSquare::render(SDL_Renderer* render, int x, int y){
  rect.x = x;
  rect.y = y;
  
  if(placed) {
    SDL_RenderCopy(render, texture, NULL, &rect);
  } else{
    SDL_RenderCopy(render, NULL, NULL, &rect);  
  }
}

void GridSquare::contains(int x, int y){}

bool GridSquare::operator==(const GridSquare& square){
    return texture == square.texture;
}

void GridSquare::free(){
  if(texture != NULL){
    std::cout << "free" << std::endl;
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}
