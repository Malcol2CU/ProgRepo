#include "menu.h"
#include <SDL.h>
#include <iostream>
#include <SDL/SDL_ttf.h>

FrameFactory*  FrameFactory::instance = NULL;
RenderContext* RenderContext::instance = NULL;

Menu::Menu() : 
   window(RenderContext::getInstance()->getWindow()),
   renderer(RenderContext::getInstance()->getRenderer()),
   menuTitle("Menu"), startTitle("Start Menu"),
   width(Gamedata::getInstance().getXmlInt("view/width")),
   height(Gamedata::getInstance().getXmlInt("view/height")),
   bg(IOmod::getInstance().readTexture("images/background/background.png")),
   font(TTF_OpenFont("fonts/arial.ttf",30)),
   engine()
{   }

Menu::~Menu(){
  delete RenderContext::getInstance();
  SDL_DestroyTexture(bg);
  TTF_CloseFont(font);
  TTF_Quit(); 
}


void Menu::showStart(){
SDL_Texture* texture;
SDL_SetWindowTitle(window, startTitle.c_str());
const int NUM = 2;
int x, y;
const char* labels[NUM] = {"Start", "Exit"};
SDL_Surface* menus[NUM];
bool selected[NUM] = {false,false};
SDL_Color color[2] = {{51,0,102,255},{255,0,0,255}};

menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);

SDL_Rect pos[NUM];
pos[0].x = width - menus[0]->w/2 - 75;
pos[0].y = 40 - menus[0]->h ;
pos[1].x = width - menus[0]->w/2 - 75;
pos[1].y = 80 - menus[0]->h;
 
SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

SDL_Event event;
while(1){
   while(SDL_PollEvent(&event)){
     switch(event.type){
        case SDL_QUIT:
           SDL_FreeSurface(menus[0]);
           SDL_FreeSurface(menus[1]);
           return;

        case SDL_MOUSEMOTION:
	   x = event.motion.x;
	   y = event.motion.y;
	   for(int i = 0; i < NUM; i++) {
	      if(x>=pos[i].x && x<=pos[i].x+menus[i]->w && y>=pos[i].y && y<=pos[i].y+menus[i]->h){
		if(!selected[i]){
		   selected[i] = 1;
		   SDL_FreeSurface(menus[i]);
		   menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
		}
	      }
	     else{
	       if(selected[i]){
		selected[i] = 0;
		SDL_FreeSurface(menus[i]);
		menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
	       }
	     }
	  }
	break;
        
        case SDL_MOUSEBUTTONDOWN:
           x = event.button.x;
           y = event.button.y;
           for(int i = 0; i < NUM; i++) {
              if(x>=pos[i].x && x<=pos[i].x+menus[i]->w && y>=pos[i].y && y<=pos[i].y+menus[i]->h){ 
                 if(i == 0){           
                 play();
		 showMenu();}
                 else return;
              }
           }
           break;

     }
   }
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, bg, NULL, NULL);
  for(int i = 0; i < NUM; i++) {
	texture = SDL_CreateTextureFromSurface(renderer, menus[i]);
	SDL_Rect dst = {pos[i].x, pos[i].y, menus[i]->w, menus[i]->h};
	SDL_RenderCopy(renderer, texture, NULL, &dst);
  }
  SDL_RenderPresent(renderer);

}
SDL_FreeSurface(menus[0]);
SDL_FreeSurface(menus[1]);
SDL_DestroyTexture(texture);
}

void Menu::showMenu(){}

void Menu::play(){
   try {
      if(engine.play()){}
      	
      
      }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
}
