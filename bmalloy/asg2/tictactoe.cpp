#include "tictactoe.h"

const int WIDTH = 600;
const int HEIGHT = 600;
const int SIZE = 128;
const int OFFSET = 35;
const float X_VEL = 150.0;
const float Y_VEL = 150.0;

TicTacToe::TicTacToe(): placed(0){
  if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    logSDLError(std::cout ,"Could not init SDL");

  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].init();
}

TicTacToe::~TicTacToe(){
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].free();

  background.free();
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

void TicTacToe::init(){
  window = SDL_CreateWindow( "Tic-Tac-Toe", SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
  
  if(window == NULL) logSDLError(std::cout, "Couldn't make a window");

  render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  
  if ( render == 0 ) logSDLError(std::cout, "No Renderer");

  background.loadTexture("images/grid.png", render, 'g');
  SDL_SetRenderDrawColor(render, 0xFF,0xFF,0xFF,0xFF);
  background.setTextureDimensions(600,600);
}

void TicTacToe::update(){
  SDL_RenderClear(render);
  background.render(render, 0, 0);
  
  for(int x = 0; x < 3; x++)
    for(int y = 0; y < 3; y++)
      grid[x][y].render(render, x*200+OFFSET, y*200+OFFSET);

  SDL_RenderPresent(render);
}

void TicTacToe::place(int x, int y){
  static char turn = 'x';
  
  x = (x/200); y = (y/200);
  
  if(grid[x][y].notEmpty()) return;
  
  switch (turn){
    case 'x': grid[x][y].loadTexture("images/x.png", render, 'x'); 
      turn = 'o';
    break;
    case 'o': grid[x][y].loadTexture("images/o.png", render, 'o'); 
      turn = 'x';
    break;
  }
  placed++;
  grid[x][y].setTextureDimensions(SIZE,SIZE); 
}

void TicTacToe:placeBar(std::string p){
    if(bar != NULL) free();
  
  bar = IMG_LoadTexture(render, p.c_str());
  if ( bar == NULL ){std::cout << "error" << std::endl;}	
  
  static float x = 0;
  static float y = 0;
  static SDL_Rect dstrect = {0, 0, 32, 32};

  static unsigned int remainder = 0u; // ***
  static unsigned int prevTicks = SDL_GetTicks();
  unsigned int currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  //if( elapsedTicks < DT ) return;

  // Generate a frame:
 // if ( makeVideo ) frameGen.makeFrame();

  float dx = X_VEL * DT * 0.001;
  x += dx;
  float dy = Y_VEL * DT * 0.001;
  y += dy;
  //x = clamp(x,0.f,WIDTH-dstrect.w);
  //y = clamp(y,0.f,HEIGHT-dstrect.h);

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  dstrect.x = x;
  dstrect.y = y;
  
   SDL_RenderCopy(render, bar, NULL, &dstrect);
  
}

void TicTacToe::placeRandom(){
  std::mt19937 gen;
  gen.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> d(0,2);
  static char turn = 'x';
  int x = d(gen), y = d(gen);
  
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
  placed++;
}

bool TicTacToe::gameOver(){
  char lineType;

  if(placed == 9) return true;
  
  if(placed >= 5){
    std::cout<< "check" << std::endl;
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
  }
  return false;
}



//Function used to output different errors to output stream
void TicTacToe::logSDLError(std::ostream &out, const std::string &msg){
  out << msg << " error: " << SDL_GetError() << std::endl;
}
