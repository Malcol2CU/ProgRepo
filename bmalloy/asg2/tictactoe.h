#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid.h"

class TicTacToe{
  public:
    TicTacToe();
    ~TicTacToe();

    void init();
    void update();
    void place(int, int);
    void placeRandom();
    bool gameOver();
    void placeBar();
    
  private:
    void logSDLError(std::ostream &out, const std::string &msg);
    SDL_Window* window;
    SDL_Renderer* render;
    int placed;
    GridSquare background, grid[3][3];
    SDL_Texture* bar;
};
#endif
