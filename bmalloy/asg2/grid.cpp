#include "grid.h"

GridSquare::GridSquare():texture(NULL),rect(), placed(false), type(' ') {}    

GridSquare::GridSquare(const std::string& path, SDL_Renderer* render, const char t):texture(NULL), rect(),placed(false),type(' '){
      rect.x = 0;
      rect.y = 0;
      loadTexture(path, render, t); 
}

void GridSquare::setTextureDimensions(int width, int height){
  rect.w = width;
  rect.h = height;
}

void GridSquare::loadTexture(const std::string &path, SDL_Renderer *render, const char t){
  if(texture != NULL) free();
  
  texture = IMG_LoadTexture(render, path.c_str());
  if ( texture == NULL ){std::cout << "error" << std::endl;}	
  placed = true;
  type = t;
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

bool GridSquare::operator==(const GridSquare& square){
	if(square.texture == NULL) return false;
    return type == square.type;
}

void GridSquare::free(){
  if(texture != NULL){
    SDL_DestroyTexture(texture);
    texture = NULL;
  }
}
