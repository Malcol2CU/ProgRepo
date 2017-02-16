#include "tictactoe.h"

const int SIZE = 128;
const int OFFSET = 35;
const int X_POS = 10;
const int Y_POS = 10;
const float X_VEL = 150.0;
const float Y_VEL = 150.0;

// Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***

TicTacToe::TicTacToe():window(NULL), render(0), placed(0), background(),
   bar(NULL), winner(NULL),barRect(), winRect(), frameGen(){
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
  SDL_DestroyTexture(bar);
  SDL_DestroyTexture(winner);
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

  frameGen.set(render, window);
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
  
  if(bar != NULL) SDL_RenderCopy(render, bar, NULL, &barRect);
  if(winner != NULL) SDL_RenderCopy(render, winner, NULL, &winRect);
  
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
  for(int x = 0; x < 30; x++) frameGen.makeFrame();
}

void TicTacToe::placeBar(std::string p, int x, int y, int w, int h, char type){
  bar = IMG_LoadTexture(render, p.c_str());
  if ( bar == NULL )logSDLError(std::cout, "bar = null");	


  switch (type){
    case 'x': winner = IMG_LoadTexture(render, "images/xwin.png"); break;
    case 'o': winner = IMG_LoadTexture(render, "images/owin.png"); break;
  }
  if ( winner == NULL )logSDLError(std::cout, "winner = null");
   
  barRect.x = x * 200;
  barRect.y = y * 200;
  barRect.w = w; barRect.h = h;
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
  for(int x = 0; x < 30; x++) frameGen.makeFrame();
  SDL_Delay( 1000 ); 
}

bool TicTacToe::gameOver(){
  if(placed >= 5){
    if(grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
      placeBar("images/ldline.png", 0, 0, 600, 600, grid[0][0].getType());
      return true;	
    }
    
    if(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]){
      placeBar("images/rdline.png", 0, 0, 600, 600, grid[0][2].getType());
      return true;	
    }
  
    for(int x = 0; x < 3; x++){
      if(grid[x][0] == grid[x][1] && grid[x][1] == grid[x][2]){
        placeBar("images/vline.png", x, 0, 200, 600, grid[x][0].getType());
        return true;
      }
    
      if(grid[0][x] == grid[1][x] && grid[1][x] == grid[2][x]){
        placeBar("images/hline.png", 0 , x, 600,200, grid[0][x].getType());
        return true;
      }
    }
  }
  if(placed == 9){
    winner = IMG_LoadTexture(render, "images/catwin.png");
    return true;
  }
  return false;
}

bool TicTacToe::animate() {
  static float x = X_POS;
  winRect.y = 250;
  winRect.w = 325; winRect.h = 128;

  static unsigned int remainder = 0u; // ***
  static unsigned int prevTicks = SDL_GetTicks();
  unsigned int currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***

  if(x > WIDTH) return true;
  float dx = X_VEL * DT * 0.001;
  x += dx;

  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  winRect.x = x;
  frameGen.makeFrame();
  return false;
}

//Function used to output different errors to output stream
void TicTacToe::logSDLError(std::ostream &out, const std::string &msg){
  out << msg << " error: " << SDL_GetError() << std::endl;
}
