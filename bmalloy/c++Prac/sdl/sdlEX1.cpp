int main(){


}

bool init(){
   //Variables
   bool success = true;

   //Initialize SDL
   if(SDL_Init(SDL_INIT_VIDEO) < 0){
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      success = false; 
   }

   //Create window 
   gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
   if( gWindow == NULL ) { 
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() ); 
      success = false; 
   } 
   else { 
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow ); 
   }  
   return success;  
}

bool loadMedia(){
   //Loading success 
   flag bool success = true; 
   
   //Load splash image 
   gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" ); 
   if( gHelloWorld == NULL ) { 
      printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
      success = false; 
   } 

   return success;
}
void close(){}
