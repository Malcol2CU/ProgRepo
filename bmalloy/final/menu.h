#ifndef MENU_H
#define MENU_H
#include "engine.h"

class Menu{
public:
  Menu();
  ~Menu();
  void showStart();

private:
  SDL_Window* const window;
  SDL_Renderer* const renderer;
  std::string menuTitle, startTitle;
  const int width, height;
  SDL_Texture* const bg;
  TTF_Font *font;
  Engine engine;


  void showMenu();
  void play();
  Menu(Menu&) = delete;
  Menu& operator=(const Menu&) = delete;
};

#endif
