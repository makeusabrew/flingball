//
// C++ Implementation: globals
//
// Description: 
//
//
// Author: Nick Payne
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <sstream>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>

using namespace std;

#include "globals.h"
#include "ball.h"
//#include "world.h"
//#include "player.h"
//#include "sound.h"
//----------------------------------------------------------
//----------------------------------------------------------

int mainEditor(int argc, char* args[]) {
	return 0;
}

int mainGame(int argc, char* args[]) {
	// for fps counter
	int startTime;
	int frameTime;
	int fps;
	
	int quit = 0;
	SDL_Surface *screen;
	// SDL init
	cout << "Starting up...(" << argc << ")" << endl;
	cout << "Initialising SDL..." << endl;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	cout << "SDL Video init OK..." << endl;
	atexit(SDL_Quit);
	// screen init
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	if (screen == NULL) {
		//fprintf(stderr, "Couldn't set 640x480x32 video mode: %s\n", SDL_GetError());
		cout << "Couldn't set " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "x" << SCREEN_HEIGHT << "x" << SCREEN_BPP << ": " << SDL_GetError() << endl;
		return 1;
	}
	//SDL_ShowCursor(SDL_DISABLE);  // get rid of cursor
	SDL_WM_SetCaption("Fling Ball", NULL);
	cout << "Set Video mode " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "x" << SCREEN_HEIGHT << " OK" << endl;

	//SDL_EnableKeyRepeat(1, 1);

	/********************
	** game init stuff **
	********************/
	//CWorld *world;  // define the world
	//CEvent eventhandler;
	//eventhandler.setPlayer(player);
/*
	world = new CWorld;

	world->setRenderingBuffer(screen);  // get a reference to the global screen
		
	if (!world->loadFromFile("data/maps/map1.wld")) {
		cout << "ERROR: Could not load default map!" << endl;
		return 1;
	}
	
	// find our player
	CPlayer* player;
	player = world->getPlayerEntity();
	if (player == NULL) {
		cout << "Could not get player object" << endl;
		SDL_Quit();
		return 1;
	}
	
	cout << "Loading world textures..." << endl;
	world->loadTexture("data/tex2.bmp");
	world->loadTexture("data/cp1.bmp");
	world->loadTexture("data/cp2.bmp");
	world->loadTexture("data/cp3.bmp");
	world->loadSky("data/skynew.bmp");
	
	player->setRenderingBuffer(screen);
	player->setSoundEngine(sound);
	// by default we have a pistol
	player->activateWeapon(WEAPON_SHOTGUN);
	player->changeWeapon(WEAPON_SHOTGUN);

	// get a new hud
	CHud *hud = new CHud;
	player->setHud(hud);
	
	world->spawnRandomEntities(20);
*/
	CBall *ball;
	ball = new CBall;
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	//FPSmanager* fpsman;
	//SDL_initFramerate(fpsman);
	//SDL_setFramerate(fpsman, 30);
	bool mouseDown = false;
	while(!quit) {
		// FPS
		startTime = SDL_GetTicks();
		
		/**************************************
		** event handling & processing stuff **
		**************************************/
		//player->stop();
		
			
		while (SDL_PollEvent(&event)) {  // we need a while loop as there may be several events in the queue
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
					
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mouseDown = true;
					}
					break;
					
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mouseDown = false;
					}
					break;					
			}
		}
		
		if (keyPressed(SDLK_ESCAPE)) {
			quit = 1;
			break;
		}
		
		if (keyPressed(SDLK_UP)) {
		//	player->moveForward();
		} else if (keyPressed(SDLK_DOWN)) {
		//	player->moveBackward();
		}
		
		if (keyPressed(SDLK_LEFT)) {
		//	player->turnLeft();
		} else if (keyPressed(SDLK_RIGHT)) {
		//	player->turnRight();
		}
		
		if (keyPressed(SDLK_a)) {
		//	player->strafeLeft();
		} else if (keyPressed(SDLK_d)) {
		//	player->strafeRight();
		}
		
		if (keyPressed(SDLK_SPACE)) {
		//	player->fireCurrentWeapon();
		}

		/*********************
		** game logic stuff **
		*********************/
		
		//player->move();  // this takes care of bound checking
		
		//player->doThinks();  // basically amounts to weapon firing / bullets and stuff
		
		//world->doEntityThinks();
			
		/********************
		** rendering stuff **
		********************/
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  // fill white every frame
		
		ball->move();
		if (mouseDown) {
			ball->setColour(255, 0, 0);
		} else {
			ball->setColour(0, 0, 0);
		}
		ball->draw(screen);
		//world->renderBackground(player->getAngle());
		//player->render(fps);  // render our view first (and render some bullets and that)
		
		//world->render();  // render the world (this actually only renders the top down map)
		//player->renderOnMap();
		//player->think();
		
		// draw hud
		//hud->draw();

		// write fps counter
		//hud->drawFPS(fps);
		
		SDL_Flip(screen);  // flip back buffer -> screen
		
		//SDL_framerateDelay(fpsman);
		
		frameTime = SDL_GetTicks()-startTime;
		fps = (frameTime>0) ? 1000 / frameTime : 0;
		SDL_Delay(25);
	}
	
	delete ball;

	cout << "Exiting..." << endl;
	SDL_Quit();
	cout << "Done." << endl;
	return 0;
}

// The following code implements a Bresenham line drawing
// algorithm. There are 4 separate routines each optimized
// for one of the four pixel depths supported by SDL. SDL
// support many pixel formats, but it only support 8, 16,
// 24, and 32 bit pixels.

//----------------------------------------------------------

// Draw lines in 8 bit surfaces.

void line8(SDL_Surface *s,
					 int x1, int y1,
			int x2, int y2,
	 Uint32 color)
{
	int d;
	int x;
	int y;
	int ax;
	int ay;
	int sx;
	int sy;
	int dx;
	int dy;

	Uint8 *lineAddr;
	Sint32 yOffset;

	dx = x2 - x1;
	ax = abs(dx) << 1;
	sx = sign(dx);

	dy = y2 - y1;
	ay = abs(dy) << 1;
	sy = sign(dy);
	yOffset = sy * s->pitch;

	x = x1;
	y = y1;

	lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
	if (ax>ay)
	{                      /* x dominant */
		d = ay - (ax >> 1);
		for (;;)
		{
			*(lineAddr + x) = (Uint8)color;

			if (x == x2)
			{
				return;
			}
			if (d>=0)
			{
				y += sy;
				lineAddr += yOffset;
				d -= ax;
			}
			x += sx;
			d += ay;
		}
	}
	else
	{                      /* y dominant */
		d = ax - (ay >> 1);
		for (;;)
		{
			*(lineAddr + x) = (Uint8)color;

			if (y == y2)
			{
				return;
			}
			if (d>=0)
			{
				x += sx;
				d -= ay;
			}
			y += sy;
			lineAddr += yOffset;
			d += ax;
		}
	}
}

//----------------------------------------------------------

// Draw lines in 16 bit surfaces. Note that this code will
// also work on 15 bit surfaces.

void line16(SDL_Surface *s,
						int x1, int y1,
			int x2, int y2,
	 Uint32 color)
{
	int d;
	int x;
	int y;
	int ax;
	int ay;
	int sx;
	int sy;
	int dx;
	int dy;

	Uint8 *lineAddr;
	Sint32 yOffset;

	dx = x2 - x1;
	ax = abs(dx) << 1;
	sx = sign(dx);

	dy = y2 - y1;
	ay = abs(dy) << 1;
	sy = sign(dy);
	yOffset = sy * s->pitch;

	x = x1;
	y = y1;

	lineAddr = ((Uint8 *)s->pixels) + (y * s->pitch);
	if (ax>ay)
	{                      /* x dominant */
		d = ay - (ax >> 1);
		for (;;)
		{
			*((Uint16 *)(lineAddr + (x << 1))) = (Uint16)color;

			if (x == x2)
			{
				return;
			}
			if (d>=0)
			{
				y += sy;
				lineAddr += yOffset;
				d -= ax;
			}
			x += sx;
			d += ay;
		}
	}
	else
	{                      /* y dominant */
		d = ax - (ay >> 1);
		for (;;)
		{
			*((Uint16 *)(lineAddr + (x << 1))) = (Uint16)color;

			if (y == y2)
			{
				return;
			}
			if (d>=0)
			{
				x += sx;
				d -= ay;
			}
			y += sy;
			lineAddr += yOffset;
			d += ax;
		}
	}
}

//----------------------------------------------------------

// Draw lines in 24 bit surfaces. 24 bit surfaces require
// special handling because the pixels don't fall on even
// address boundaries. Instead of being able to store a
// single byte, word, or long you have to store 3
// individual bytes. As a result 24 bit graphics is slower
// than the other pixel sizes.

void line24(SDL_Surface *s,
						int x1, int y1,
			int x2, int y2,
	 Uint32 color)
{
	int d;
	int x;
	int y;
	int ax;
	int ay;
	int sx;
	int sy;
	int dx;
	int dy;

	Uint8 *lineAddr;
	Sint32 yOffset;

#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	color <<= 8;
#endif

	dx = x2 - x1;
	ax = abs(dx) << 1;
	sx = sign(dx);

	dy = y2 - y1;
	ay = abs(dy) << 1;
	sy = sign(dy);
	yOffset = sy * s->pitch;

	x = x1;
	y = y1;

	lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
	if (ax>ay)
	{                      /* x dominant */
		d = ay - (ax >> 1);
		for (;;)
		{
			Uint8 *p = (lineAddr + (x * 3));
			memcpy(p, &color, 3);

			if (x == x2)
			{
				return;
			}
			if (d>=0)
			{
				y += sy;
				lineAddr += yOffset;
				d -= ax;
			}
			x += sx;
			d += ay;
		}
	}
	else
	{                      /* y dominant */
		d = ax - (ay >> 1);
		for (;;)
		{
			Uint8 *p = (lineAddr + (x * 3));
			memcpy(p, &color, 3);

			if (y == y2)
			{
				return;
			}
			if (d>=0)
			{
				x += sx;
				d -= ay;
			}
			y += sy;
			lineAddr += yOffset;
			d += ax;
		}
	}
}

//----------------------------------------------------------

// Draw lines in 32 bit surfaces. Note that this routine
// ignores alpha values. It writes them into the surface
// if they are included in the pixel, but does nothing
// else with them.

void line32(SDL_Surface *s,
						int x1, int y1,
			int x2, int y2,
	 Uint32 color)
{
	int d;
	int x;
	int y;
	int ax;
	int ay;
	int sx;
	int sy;
	int dx;
	int dy;

	Uint8 *lineAddr;
	Sint32 yOffset;

	dx = x2 - x1;
	ax = abs(dx) << 1;
	sx = sign(dx);

	dy = y2 - y1;
	ay = abs(dy) << 1;
	sy = sign(dy);
	yOffset = sy * s->pitch;

	x = x1;
	y = y1;

	lineAddr = ((Uint8 *)(s->pixels)) + (y * s->pitch);
	if (ax>ay)
	{                      /* x dominant */
		d = ay - (ax >> 1);
		for (;;)
		{
			*((Uint32 *)(lineAddr + (x << 2))) = (Uint32)color;

			if (x == x2)
			{
				return;
			}
			if (d>=0)
			{
				y += sy;
				lineAddr += yOffset;
				d -= ax;
			}
			x += sx;
			d += ay;
		}
	}
	else
	{                      /* y dominant */
		d = ax - (ay >> 1);
		for (;;)
		{
			*((Uint32 *)(lineAddr + (x << 2))) = (Uint32)color;

			if (y == y2)
			{
				return;
			}
			if (d>=0)
			{
				x += sx;
				d -= ay;
			}
			y += sy;
			lineAddr += yOffset;
			d += ax;
		}
	}
}


//----------------------------------------------------------

// Examine the depth of a surface and select a line
// drawing routine optimized for the bytes/pixel of the
// surface.

void line(SDL_Surface *s,
					int x1, int y1,
		 int x2, int y2,
	 Uint32 color)
{
	switch (s->format->BytesPerPixel)
	{
		case 1:
			line8(s, x1, y1, x2, y2, color);
			break;
		case 2:
			line16(s, x1, y1, x2, y2, color);
			break;
		case 3:
			line24(s, x1, y1, x2, y2, color);
			break;
		case 4:
			line32(s, x1, y1, x2, y2, color);
			break;
	}
}

bool keyPressed(SDLKey key)
{
	Uint8* keyState = SDL_GetKeyState(NULL);
	
	if(key < 0 || key >= 322)
	{
		return false;
	}
	
	return keyState[key];
}
