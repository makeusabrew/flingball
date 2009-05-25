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
#include "Include/Box2D.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_W SCREEN_WIDTH
#define SCREEN_H SCREEN_HEIGHT
#define SCREEN_BPP 32

#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600
#define VIEWPORT_W VIEWPORT_WIDTH
#define VIEWPORT_H VIEWPORT_HEIGHT

#define VIEWPORT_X 0
#define VIEWPORT_Y 0

#define CAMERA_MOVE_THRESHOLD 180

/******************************
* EDITOR STUFF
******************************/

#define EDITOR_SCREEN_WIDTH 1024
#define EDITOR_SCREEN_HEIGHT 768
#define EDITOR_SCREEN_W EDITOR_SCREEN_WIDTH
#define EDITOR_SCREEN_H EDITOR_SCREEN_HEIGHT
#define EDITOR_SCREEN_BPP 32

#define EDITOR_VIEWPORT_WIDTH 1024
#define EDITOR_VIEWPORT_HEIGHT 768
#define EDITOR_VIEWPORT_W EDITOR_VIEWPORT_WIDTH
#define EDITOR_VIEWPORT_H EDITOR_VIEWPORT_HEIGHT

#define EDITOR_VIEWPORT_X 0
#define EDITOR_VIEWPORT_Y 0

const float32 DEFAULT_METRES_TO_PIXELS = 40.0f;
const float32 MAX_METRES_TO_PIXELS = 100.0f;
const float32 MIN_METRES_TO_PIXELS = 20.0f;
// e.g. 1 metre = 50 pixels

const float32 WORLD_BOUNDARY_FRICTION = 0.5f;
const float32 WORLD_BOUNDARY_THICKNESS = 0.5f;

const float32 BALL_ROLLING_FRICTION = 0.03f;

const float32 MAX_FLING_DRAG = 180.0f;

#define DATA_STATIC 0
#define DATA_END_POINT 1
#define DATA_BALL 2

#define E_READY 0
#define E_SHAPING 1
#define E_MOVING 2


#ifndef PI
#define PI 3.14159265
#endif

#define DEBUG 1

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
	float32 x;
	float32 y;
} Point;

class CCamera;
class CLevel;

extern SDL_Surface *screen;
extern CCamera camera;
extern CLevel* level;

#endif
