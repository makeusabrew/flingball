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
#include "level.h"
//#include "player.h"
//#include "sound.h"
//----------------------------------------------------------
//----------------------------------------------------------

SDL_Surface *screen;

int mainEditor(int argc, char* args[]) {
	return 0;
}

int mainGame(int argc, char* args[]) {
	// for fps counter
	int startTime;
	int frameTime;
	int fps;
	
	int quit = 0;
	
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
	
	CLevel *level;
	level = new CLevel;
	
	level->loadDataFromFile("data/maps/1.lvl");
	
	cout << level->getTitle() << endl;

	CBall *ball;
	ball = new CBall;
	ball->setCoords(level->getStartPoint());
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	
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
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));  // black layer
		
		SDL_Rect rect;
		rect.x = VIEWPORT_X;
		rect.y = VIEWPORT_Y;
		rect.w = VIEWPORT_W;
		rect.h = VIEWPORT_H;
		SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));	// white game area
		
		
		ball->move(level);
		if (mouseDown) {
			ball->setColour(255, 0, 0);
		} else {
			ball->setColour(0, 0, 0);
		}
		level->render();
		ball->render();
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
	delete level;

	cout << "Exiting..." << endl;
	SDL_Quit();
	cout << "Done." << endl;
	return 0;
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
