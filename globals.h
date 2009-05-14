//
// C++ Interface: globals
//
// Description: global variable / macro / function declarations
//
//
// Author: Nick Payne
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_GLOBALS_H
#define INC_GLOBALS_H
#include <string>
#include <SDL/SDL.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_W SCREEN_WIDTH
#define SCREEN_H SCREEN_HEIGHT
#define SCREEN_BPP 32

#ifndef PI
#define PI 3.14159265
#endif

extern SDL_Surface *screen;

const int ENTITY_TYPE_PLAYER = 0;
const int ENTITY_TYPE_ENEMY = 1;
const int ENTITY_TYPE_PICKUP = 2;
const int ENTITY_TYPE_BULLET = 3;

// A set of very useful macros that you will find in most
// code that I write whether I use them in a program or
// not.

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define abs(a) (((a)<0) ? -(a) : (a))
#define sign(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)
#define deg2rad(a) (a*(PI/180))

void line(SDL_Surface *s,
					int x1, int y1,
		 int x2, int y2,
	 Uint32 color);

int mainEditor(int argc, char* args[]);
int mainGame(int argc, char* args[]);

bool keyPressed(SDLKey key);

#endif
