#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid.h"
#include "frameGenerator.h"

class TicTacToe{
  public:
    TicTacToe();
    ~TicTacToe();

    void init();
    void update();
    void place(int, int);
    void placeRandom();
    bool gameOver();
    void placeBar(std::string, int, int, int, int, char);
    bool animate();
    TicTacToe(const TicTacToe&) = delete;
    TicTacToe operator=(const TicTacToe&) = delete;
    
  private:
    void logSDLError(std::ostream &out, const std::string &msg);
    SDL_Window* window;
    SDL_Renderer* render;
    int placed;
    GridSquare background, grid[3][3];
    SDL_Texture* bar, *winner;
    SDL_Rect barRect, winRect;
    FrameGenerator frameGen;
    bool over;
};
#endif
