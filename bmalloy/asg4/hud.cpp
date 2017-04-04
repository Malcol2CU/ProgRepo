#include "hud.h"
#include "renderContext.h"
#include "gamedata.h"
#include <sstream>

Hud::Hud(): 
  hud(), 
  renderer(RenderContext::getInstance()->getRenderer()),
  io( IOmod::getInstance() ),
alpha(255/2)
{}
Hud::~Hud(){


}

void Hud::display(){
   alpha = 255;
}

void Hud::draw(int x, int y, int w, int h, int fps, int ticks){
    if (ticks > 3)
       if (alpha != 0) alpha--;
	hud.x = x;
	hud.y = y;
	hud.w = w;
	hud.h = h;

	 // First set the blend mode so that alpha blending will work;
	// the default blend mode is SDL_BLENDMODE_NONE!
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, alpha );

	// Render rect
	SDL_RenderFillRect( renderer, &hud );

	SDL_SetRenderDrawColor( renderer, 255, 0, 0, alpha );
	SDL_RenderDrawRect( renderer, &hud );

	std::stringstream strm, strm1, strm2, strm3, strm4;
	SDL_Color color = {255, 50, 50, 0};
     
    if (alpha == 0) return;
	io.writeText(Gamedata::getInstance().getXmlStr("username"),
	Gamedata::getInstance().getXmlFloat("view/width")/2.4,0, color);
	strm << "fps: " << fps << " Time: " << ticks; 
    strm1 <<"w & Up Arrow: Jump"; 
    strm2 << "d & rightArrow: Move right";
    strm3 << "na & leftArrow: Move left"; 
    strm4 << "Space Bar: Attack";
	io.writeText(strm.str(), 10, 10, color);
	io.writeText(strm1.str(), 10, 40, color);
	io.writeText(strm2.str(), 10, 70, color);
	io.writeText(strm3.str(), 10, 100, color);
	io.writeText(strm4.str(), 10, 130, color);
}
