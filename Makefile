all:
	g++ -Wall *.cpp -o main.o `sdl-config --libs` -lSDL_mixer -lSDL_gfx
