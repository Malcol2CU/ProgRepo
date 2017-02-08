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

//Function used to output different errors to output stream
void logSDLError(std::ostream &out, const std::string &msg){
  out << msg << " error: " << SDL_GetError() << std::endl;
}

//Inits window and returns pointer to it
SDL_Window* initWindow( ) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) logSDLError(std::cout ,"Could not init SDL");
  
  SDL_Window* window = 
	  SDL_CreateWindow( "Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, 
       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  
  if(window == NULL) logSDLError(std::cout, "Couldn't make a window");
  
  return window;
}

//Inits renderer and returns pointer to it
SDL_Renderer* initRenderer(SDL_Window* window) {
  SDL_Renderer* render = 
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if ( render == 0 ) logSDLError(std::cout, "No Renderer");
  
  return render;
}

//Updates the renderer with new textures
void update(GridSquare& bg, GridSquare grid[3][3], SDL_Renderer* render){
  SDL_RenderClear(render);
  bg.render(render, 0, 0);
  
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].render(render, x*200+OFFSET, y*200+OFFSET);

  SDL_RenderPresent(render);
}

//Place Function for computer player
void placeRandom(GridSquare grid[3][3], SDL_Renderer* render){
  std::mt19937 gen;
  gen.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> d(0,2);
  static char turn = 'x';
  static int count = 1;
  int x = d(gen), y = d(gen);
  
  if(count > 9 ) return;
  
  while(grid[x][y].notEmpty()){
    x = d(gen); y = d(gen);
  }
  
  switch (turn){
	case 'x': grid[x][y].loadTexture("images/x.png", render, 'x'); 
	  turn = 'o';
	  break;
	case 'o': grid[x][y].loadTexture("images/o.png", render, 'o'); 
	  turn = 'x';
	  break;
  }

  grid[x][y].setTextureDimensions(SIZE,SIZE);
  count++;
}

//Place function for human player
void place(GridSquare grid[3][3], SDL_Renderer* render, int x, int y){
  static char turn = 'x';
  
  x = (x/200); y = (y/200);
  
  if(count > 9 || grid[x][y].notEmpty() ) return;
  
  switch (turn){
	  case 'x': grid[x][y].loadTexture("images/x.png", render, 'x'); 
	    turn = 'o';
    break;
	  case 'o': grid[x][y].loadTexture("images/o.png", render, 'o'); 
	    turn = 'x';
    break;
  }

  grid[x][y].setTextureDimensions(SIZE,SIZE);
  count++;  
}

//Checks if Game is over and returns boolean value
bool gameOver(GridSquare grid[3][3]){
  char lineType;
  if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
     return true;	
  }
  
  for(int x = 0; x < 3; x++){
    if(grid[x][0] == grid[x][1] && grid[x][1] == grid[x][2]){
      return true;
    }
    
    if(grid[0][x] == grid[1][x] && grid[1][x] == grid[2][x]){
      return true;
    }
  }
  return false;
}

int main(){
	
  //Variable Declarations 
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> window(initWindow(), SDL_DestroyWindow);
  SDL_Renderer* render = initRenderer(window.get());
  GridSquare background("images/grid.png", render, 'g'), grid[3][3];
  
  //Sets up renderColor to white and sets background grid dimensions
  SDL_SetRenderDrawColor(render, 0xFF,0xFF,0xFF,0xFF);
  background.setTextureDimensions(600,600);
  
  //Gameloop
  while(true && !gameOver(grid)){
    keystate = SDL_GetKeyboardState(&nKeys);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
      if (event.type == SDL_MOUSEBUTTONDOWN){
          int x = event.button.x;
          int y = event.button.y;
          place(grid, render, x, y);
      }
    }
    
    //if (SDL_GetTicks() > 17000) break;
    //placeRandom(grid, render);
    update(background, grid, render);
  }

  //Frees memory
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].free();
  background.free();
  SDL_DestroyRenderer(render);
  IMG_Quit();
  SDL_Quit();
  return 0;
}
