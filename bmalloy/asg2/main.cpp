#include <iostream>
#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid.h"

//Global CONST Variables
const int WIDTH = 600;
const int HEIGHT = 600;
const int SIZE = 128;
const int OFFSET = 35;

void logSDLError(std::ostream &out, const std::string &msg){
  out << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Window* initWindow( ) {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
	throw (std::string("Could not init SDL: ") + SDL_GetError());
  }
  SDL_Window* window = 
	SDL_CreateWindow( "Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, 
       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    throw (std::string("Couldn't make a window: ")+SDL_GetError());
  }
  return window;
}

SDL_Renderer* initRenderer(SDL_Window* window) {
  SDL_Renderer* render = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if ( render == 0 ) throw std::string("No Renderer");
  return render;
}

SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *render){
  SDL_Texture *texture = IMG_LoadTexture(render, path.c_str());
  if ( texture == NULL ){ logSDLError(std::cout, "Couldn'tLoadImage");}
  return texture;	
}

void update(GridSquare& bg, GridSquare grid[3][3], SDL_Renderer* render){
  SDL_RenderClear(render);
  bg.render(render, 0, 0);
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].render(render, x*200+OFFSET, y*200+OFFSET);

  SDL_RenderPresent(render);
  SDL_Delay(2000);
}

void place(GridSquare grid[3][3], SDL_Renderer* render){
  std::mt19937 gen;
  gen.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> d(0,2);
  int x, y;
  x = d(gen);
  y = d(gen);
  std::cout << x << y << std::endl;
  grid[x][y].loadTexture("images/x.png", render);
  grid[x][y].setTextureDimensions(SIZE,SIZE);
}

int main(){
	
  //Variable Declarations 
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  
  std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window(initWindow(), SDL_DestroyWindow);
  SDL_Renderer* render = initRenderer(window.get());
  SDL_SetRenderDrawColor(render, 0xFF,0xFF,0xFF,0xFF);
  GridSquare background("images/grid.png", render), grid[3][3];
  background.setTextureDimensions(600,600);
  
  while(true){
    keystate = SDL_GetKeyboardState(&nKeys);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
    
    if (SDL_GetTicks() > 6000) break;
    
    place(grid, render);
    update(background, grid, render);
    
  }
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].free();
  background.free();
  SDL_DestroyRenderer(render);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
