#include "menu.h"
#include <SDL.h>
#include <iostream>
#include <SDL/SDL_ttf.h>

FrameFactory*  FrameFactory::instance = NULL;
RenderContext* RenderContext::instance = NULL;

Menu::Menu() : 
   engine(),
   window(RenderContext::getInstance()->getWindow()),
   renderer(RenderContext::getInstance()->getRenderer()),
   menuTitle("Menu"), startTitle("Start Menu"),
   width(Gamedata::getInstance().getXmlInt("view/width")),
   height(Gamedata::getInstance().getXmlInt("view/height")),
   bg(IOmod::getInstance().readTexture("images/background/background.png")),
   font(TTF_OpenFont("fonts/arial.ttf",30))
{   }

Menu::~Menu(){
std::cout << "menu deconstructor" << std::endl;
  SDL_DestroyTexture(bg);
  TTF_CloseFont(font); 
  delete RenderContext::getInstance();
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
           SDL_DestroyTexture(texture);
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
                 if(i == 0){  choosePlayer();}
                 else{ std::cout << "menu deletes" << std::endl;
			SDL_FreeSurface(menus[0]);
			SDL_FreeSurface(menus[1]);
			SDL_DestroyTexture(texture);
		    return;}
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
  engine.makeFrame();

}
}

void Menu::showMenu(){}

void Menu::choosePlayer(){
const char* labels[3] = {"Grim", "Billy", "Choose Character"};
SDL_Surface* names[3];


SDL_Texture* texture;
SDL_Texture* characters[2];
characters[0] = IOmod::getInstance().readTexture("images/choose/grim.png");
characters[1] = IOmod::getInstance().readTexture("images/choose/billy.png");
int offset = 5, dim = 180, x ,y;
SDL_Color w = {255,255,255,255}, r = {51,0,102,255};
names[0] = TTF_RenderText_Solid(font,labels[0],r);
names[1] = TTF_RenderText_Solid(font,labels[1],r);
names[2] = TTF_RenderText_Solid(font,labels[2],r);
bool selected[2] = {false,false};

SDL_Rect pos[2];
pos[0].x = width/2-200;
pos[0].y = height/2 - 100 ;
pos[1].x = width/2+75;
pos[1].y = height/2 - 100;
SDL_Rect iRect[2] = {{pos[0].x, pos[0].y, dim, dim},  {pos[1].x, pos[1].y, dim, dim}};
SDL_Rect oRect[2] = {{pos[0].x-offset, pos[0].y-offset, dim+2*offset, dim+2*offset},
   {pos[1].x-offset, pos[1].y-offset, dim+2*offset, dim+2*offset}};

SDL_Rect words[3] = {{pos[0].x+15, pos[0].y+dim, names[0]->w, names[0]->h}, 
 {pos[1].x+75, pos[1].y+dim, names[1]->w, names[1]->h}, { width/2-names[2]->w/2, 50, names[2]->w, names[2]->h}};


SDL_Event event;
while(1){
SDL_RenderClear(renderer);
   while(SDL_PollEvent(&event)){
     switch(event.type){
        case SDL_QUIT:
           return;
        case SDL_MOUSEMOTION:
	   x = event.motion.x;
	   y = event.motion.y;
	   for(int i = 0; i < 2; i++) {
	      if(x>=pos[i].x && x<=pos[i].x+dim && y>=pos[i].y && y<=pos[i].y+dim){
		if(!selected[i]) selected[i] = true;}
	     else if(selected[i]) selected[i] = false;
	  }
	  break;
        case SDL_MOUSEBUTTONDOWN:
           x = event.button.x; y = event.button.y;
           for(int i = 0; i < 2; i++) {
              if(x>=pos[i].x && x<=pos[i].x+dim && y>=pos[i].y && y<=pos[i].y+dim){ 
                 if(i == 0){engine.setCharacter(0);}
		 else{engine.setCharacter(1);}
                 play();
              }
           }
           break;	

     }
   }
   
   for(int i = 0; i < 2; i++){
      if(selected[i]){
	SDL_SetRenderDrawColor( renderer, r.r, r.g, r.b, r.a );
	SDL_RenderFillRect( renderer, &oRect[i] );
	SDL_RenderCopy(renderer, NULL, NULL, &oRect[i]);
      }
     SDL_SetRenderDrawColor( renderer, w.r, w.g, w.b, w.a );
     SDL_RenderFillRect( renderer, &iRect[i] );
     SDL_RenderCopy(renderer, characters[i], NULL, &iRect[i]);
     texture = SDL_CreateTextureFromSurface(renderer, names[i]);
     SDL_RenderCopy(renderer, texture, NULL, &words[i]);
   }   
     texture = SDL_CreateTextureFromSurface(renderer, names[2]);
     SDL_RenderCopy(renderer, texture, NULL, &words[2]);
  SDL_RenderPresent(renderer);
engine.makeFrame();
}
}

void Menu::play(){
   try {
      if(engine.play()){}
      	
      
      }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
}
