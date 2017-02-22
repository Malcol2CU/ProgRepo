#include <string>
#include <SDL.h>

const int WIDTH  = 600;
const int HEIGHT = 600;
const std::string USERNAME = "malcol2";
const int unsigned MAX_FRAMES = 500;


class FrameGenerator {
public:
  FrameGenerator():  rend(0), window(NULL), frameCount(0){};
  FrameGenerator(SDL_Renderer* const r, SDL_Window* const win) : 
    rend(r), window(win),
    frameCount(0) 
  {}
  ~FrameGenerator(){
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    }
  void set(SDL_Renderer* const r, SDL_Window* const win){
    rend = r;    window = win;
  }
  void makeFrame();
  unsigned int getFrameCount() const { return frameCount; }
private:
  SDL_Renderer*  rend;
  SDL_Window*  window;
  unsigned int frameCount;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};
