#include <iostream>
#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tictactoe.h"


int main(){
  //Variable Declarations 
  SDL_Event event;
  const Uint8* keystate;
  int nKeys=-1;
  TicTacToe game;
  game.init();  

  //Gameloop
  while(!game.gameOver()){
    keystate = SDL_GetKeyboardState(&nKeys);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }

    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
      /*if (event.type == SDL_MOUSEBUTTONDOWN && !game.gameOver()){
          int x = event.button.x;
          int y = event.button.y;
          game.place(x, y);
      }*/
    }
    
    game.placeRandom();
    game.update();
    while(game.gameOver()) {
      if(game.animate()) break;
      game.update();
    }
  }

  SDL_Delay( 2000 ); 
  return 0;
}
