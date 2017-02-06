#include "grid.h"

GridSquare::GridSquare(): width(0),placed(false){
	start_pos.x = 0;
	start_pos.y = 0;
}    

GridSquare::~GridSquare(){
	SDL_DestroyTexture(texture);
}

void GridSquare::setPosition(int x, int y, int w){
  start_pos.x = x;
  start_pos.y = y;
  width = w;

  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = w;
}

void GridSquare::place(const std::string &path, SDL_Renderer *render){
  texture = IMG_LoadTexture(render, path.c_str());
  if ( texture == NULL ){std::cout << "error" << std::endl;}	
  placed = true;
}

void GridSquare::render(SDL_Renderer* render){
  if(placed) {
    SDL_RenderCopy(render, texture, NULL, &rect);
  } else{
    SDL_RenderCopy(render, NULL, NULL, &rect);  
  }
}

void GridSquare::contains(int x, int y){}
