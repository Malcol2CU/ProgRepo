# Change the following values to suit your system.

CFLAGS=`sdl2-config --cflags` -std=c++11 -g -W -Wall -Weffc++ -Wextra -pedantic -O0 -I `sdl2-config --prefix`/include/
SDL_LIB=`sdl2-config --libs` -lSDL2_image
CCC=g++

OBJECTS = frameGenerator.o tictactoe.o grid.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp tictactoe.h
	$(CCC) $(CFLAGS) -c main.cpp

frameGenerator.o: frameGenerator.cpp frameGenerator.h 
	$(CCC) $(CFLAGS) -c frameGenerator.cpp
	
tictactoe.o: tictactoe.cpp tictactoe.h frameGenerator.h
	$(CCC) $(CFLAGS) -c tictactoe.cpp
	
grid.o: grid.cpp grid.h
	$(CCC) $(CFLAGS) -c grid.cpp

clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
