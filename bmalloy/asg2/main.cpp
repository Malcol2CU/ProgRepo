#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "wtexture.h"

//Global Variables
const int WIDTH = 600;
const int HEIGHT = 600;

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


void close(){}


int main(){
	
  //Variable Declarations 
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> 
	window(initWindow(), SDL_DestroyWindow);
  
  std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> 
	render(initRenderer(window.get()), SDL_DestroyRenderer);
  
  std::unique_ptr<SDL_Texture, void (*)(SDL_Texture*)> 
	grid(loadTexture("images/grid.png", render.get()), SDL_DestroyTexture);
	
  while(true){
	while(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT) return 0;
		SDL_RenderClear(render.get());
		SDL_RenderCopy(render.get(), grid.get(), NULL, NULL);
		SDL_RenderPresent(render.get()); 
	}  
  }
  
  IMG_Quit();
  SDL_Quit();
  return 0;
}
