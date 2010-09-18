all:
	g++ *.cpp Source/Dynamics/*.cpp Source/Dynamics/Contacts/*.cpp Source/Dynamics/Joints/*.cpp Source/Common/*.cpp Source/Collision/*.cpp Source/Collision/Shapes/*.cpp  -o main.o `sdl-config --libs` -lSDL_mixer -lSDL_gfx -lSDL_ttf
