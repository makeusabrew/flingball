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

#define VIEWPORT_WIDTH 640
#define VIEWPORT_HEIGHT 480
#define VIEWPORT_W VIEWPORT_WIDTH
#define VIEWPORT_H VIEWPORT_HEIGHT

#define VIEWPORT_X (SCREEN_W - VIEWPORT_W) / 2
#define VIEWPORT_Y 20

#ifndef PI
#define PI 3.14159265
#endif

#define DEBUG 1

const int ENTITY_TYPE_PLAYER = 0;
const int ENTITY_TYPE_ENEMY = 1;
const int ENTITY_TYPE_PICKUP = 2;
const int ENTITY_TYPE_BULLET = 3;

#define RVX(x) (x + VIEWPORT_X)
#define RVY(y) (y + VIEWPORT_Y)

#define AVX(x) (x - VIEWPORT_X)
#define AVY(y) (y - VIEWPORT_Y)

// A set of very useful macros that you will find in most
// code that I write whether I use them in a program or
// not.

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define abs(a) (((a)<0) ? -(a) : (a))
#define sign(a) (((a)<0) ? -1 : (a)>0 ? 1 : 0)
#define deg2rad(a) (a*(PI/180))

int mainEditor(int argc, char* args[]);
int mainGame(int argc, char* args[]);

bool keyPressed(SDLKey key);

typedef struct{
	int x;
	int y;
} Point;

extern SDL_Surface *screen;


#endif
