#ifndef MENU_H
#define MENU_H
#include "engine.h"

class Menu{
public:
  Menu();
  ~Menu();
  void showStart();

private:
  Engine engine;
  SDL_Window* const window;
  SDL_Renderer* const renderer;
  std::string menuTitle, startTitle;
  const int width, height;
  SDL_Texture* const bg;
  TTF_Font *font;



  void showMenu();
  void play();
  void choosePlayer();
  Menu(Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
};

#endif
