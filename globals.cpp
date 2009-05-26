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
#include <fstream>

#include <SDL/SDL.h>
#include <SDL/SDL_framerate.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>
#include "Include/Box2D.h"

using namespace std;

#include "globals.h"
#include "ball.h"
#include "level.h"
#include "camera.h"
//#include "player.h"
//#include "sound.h"
//----------------------------------------------------------
//----------------------------------------------------------
SDL_Surface *screen;
CCamera camera;
CLevel *level;

int mainEditor(int argc, char* args[]) {
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
	screen = SDL_SetVideoMode(EDITOR_SCREEN_WIDTH, EDITOR_SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	if (screen == NULL) {
		//fprintf(stderr, "Couldn't set 640x480x32 video mode: %s\n", SDL_GetError());
		cout << "Couldn't set " << EDITOR_SCREEN_WIDTH << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_BPP << ": " << SDL_GetError() << endl;
		return 1;
	}
	SDL_WM_SetCaption("Fling Ball Editor", NULL);
	cout << "Set Video mode " << EDITOR_SCREEN_WIDTH << "x" << EDITOR_SCREEN_HEIGHT << "x" << EDITOR_SCREEN_HEIGHT << " OK" << endl;
	
	//CLevel *level;
	//level = new CLevel;
	
	camera.setViewport(EDITOR_VIEWPORT_X, EDITOR_VIEWPORT_Y, EDITOR_VIEWPORT_W, EDITOR_VIEWPORT_H);
	
	camera.translateTo(10, 10);	// this offsets the camera by 10 pixels so we can see the top / left of the world
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	
	int mouseX = 0;
	int mouseY = 0;
	
	int eState = E_READY;
	
	CPath paths[512];
	int cPath = 0;
	int numPaths = 0;
	
	int w = 0;
	int h = 0;
	
	float32 sX = 0;
	float32 sY = 0;
	
	string title = "Test Level";
	
	int endShape = 1;
	
	int moveShape = -1;
	int moveVertex = -1;
	
	if (strcmp(args[2], "--load") == 0) {
		// mm k, load instead
		ifstream fin;
		fin.open(args[3]);
		getline(fin, title);    // first line is title  
		fin >> w >> h;
		fin >> sX >> sY;
		fin >> numPaths;
		fin >> endShape;
		for (int i = 0; i < numPaths; i++) {
			int length = 0;
			fin >> length;
			for (int j = 0; j < length; j++) {
				float x = 0;
				float y = 0;
				fin >> x >> y;
				paths[i].addPoint(x, y);
			}
		}
		fin.close();
	} else {
		std::string sw = args[2];
		w = (atoi(sw.c_str()));
		
		std::string sh = args[3];
		h = (atoi(sh.c_str()));
	}
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
						if (eState == E_MOVING) {
							// find the poly. set move mode on it
							for (int i = 0; i < numPaths; i++) {
								if (paths[i].isPointCenter(event.button.x, event.button.y)) {
									// moving centre of poly. great!
									moveShape = i;
									moveVertex = -1;	// no vertex, whole shape
									cout << "moving entire shape, index " << moveShape << endl;
									break;
								} else {
									int vTemp = paths[i].isPointInVertex(event.button.x, event.button.y);
									if (vTemp > -1) {
										moveShape = i;
										moveVertex = vTemp;
										cout << "moving shape " << moveShape << ", vertex " << moveVertex << endl;
									}
								}
							}
						}
					}
					break;
					
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (eState == E_SHAPING) {
							// new vertex for this shape
							paths[cPath].addRelPoint(event.button.x, event.button.y);
						} else if (eState == E_MOVING) {
							// release move
							moveShape = -1;
							moveVertex = -1;
						}
					}
					break;
								
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;
					
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_s:
							if (eState == E_SHAPING) {
								cout << "Press F to finish shaping..." << endl;
							} else {
								numPaths ++;	// add a path
								cPath = numPaths - 1;	// the current path we're editing is the last (cos it's new)
								eState = E_SHAPING;
								cout << "Shaping mode: shape index " << cPath << endl;
							}
							break;
							
						case SDLK_f:
							if (eState == E_SHAPING) {
								if (paths[cPath].isValid()) {
									eState = E_READY;
									cout << "Finished shape " << cPath << endl;
								} else {
									cout << paths[cPath].getValidationError() << endl;
								}
							} else if (eState == E_MOVING) {
								eState = E_READY;
								cout << "Finished move" << endl;
							}
							break;
							
						case SDLK_b:
							sX = camera.x2a(mouseX);
							sY = camera.y2a(mouseY);
							cout << "Ball start point: " << sX << " " << sY << endl;
							break;
							
						case SDLK_m:
							if (eState == E_READY) {
								cout << "Move mode" << endl;
								eState = E_MOVING;
							}
							break;
							
						case SDLK_d:
							// done
							if (eState == E_READY) {
								cout << "Saving file..." << endl;
								ofstream fout;
								fout.open("test.lvl");
								fout << "Test Level" << endl;
								fout << w << " " << h << endl;
								fout << sX << " " << sY << endl;
								fout << numPaths << endl;
								fout << "1" << endl;
								for (int i = 0; i < numPaths; i++) {
									fout << paths[i].getLength();
									for (int j = 0; j < paths[i].getLength(); j++) {
										Point p = paths[i].getPoint(j);
										fout << " " << p.x << " " << p.y;
									}
									fout << endl;
								}
								fout.close();
								cout << "Done." << endl;
							}
							break;
					}
					break;
			}
		}
		
		if (keyPressed(SDLK_ESCAPE)) {
			quit = 1;
			break;
		}
		
		if (keyPressed(SDLK_UP)) {
			camera.translate(0, camera.m2p(0.25));
		} else if (keyPressed(SDLK_DOWN)) {
			camera.translate(0, camera.m2p(-0.25));
		}
		
		if (keyPressed(SDLK_LEFT)) {
			camera.translate(camera.m2p(0.25), 0);
		} else if (keyPressed(SDLK_RIGHT)) {
			camera.translate(camera.m2p(-0.25), 0);
		}
		
		if (keyPressed(SDLK_z)) {
			camera.zoomOut();
		} else if (keyPressed(SDLK_x)) {
			camera.zoomIn();
		}
		
		/********************
		** rendering stuff **
		********************/
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  // white layer
			
		lineRGBA(screen, camera.x2r(0), camera.y2r(0), camera.x2r(w), camera.y2r(0), 0, 0, 0, 255);
		lineRGBA(screen, camera.x2r(0), camera.y2r(h), camera.x2r(w), camera.y2r(h), 0, 0, 0, 255);
		lineRGBA(screen, camera.x2r(0), camera.y2r(0), camera.x2r(0), camera.y2r(h), 0, 0, 0, 255);
		lineRGBA(screen, camera.x2r(w), camera.y2r(0), camera.x2r(w), camera.y2r(h), 0, 0, 0, 255);
		
		for (int i = 0; i < numPaths; i++) {
			paths[i].render();
			if (eState == E_SHAPING && i == cPath) {
				paths[i].lineToPoint(mouseX, mouseY);
			} else {
				// finished
				paths[i].renderLastPoint();
			}
			
			if (eState == E_MOVING) {
				paths[i].renderHalos();
				// got index?
				if (i == moveShape) {
					if (moveVertex == -1) {
						paths[i].moveToRelPoint(mouseX, mouseY);
					} else {
						paths[i].moveVertexToRelPoint(moveVertex, mouseX, mouseY);
					}
				}
			}
		}
		
		int dx = camera.x2r(sX);
		int dy = camera.y2r(sY);
		int dr = camera.m2p(0.32f);
		circleRGBA(screen, dx, dy, dr, 128, 10, 0, 255);
		
		
			
		SDL_Flip(screen);  // flip back buffer -> screen
		
		//SDL_framerateDelay(fpsman);
		
		frameTime = SDL_GetTicks()-startTime;
		fps = (frameTime>0) ? 1000 / frameTime : 0;
		SDL_Delay(25);
	}
	
	delete level;

	cout << "Exiting..." << endl;
	SDL_Quit();
	cout << "Done." << endl;
	return 0;
}

int mainGame(int argc, char* args[]) {
	// for fps counter
	int startTime;
	int frameTime;
	int fps;
	
	int quit = 0;
	char strBuffer[80];
	
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
	
	if (TTF_Init() < 0) {
		return 1;
	}
	atexit(TTF_Quit);
	//SDL_ShowCursor(SDL_DISABLE);  // get rid of cursor
	SDL_WM_SetCaption("Fling Ball", NULL);
	cout << "Set Video mode " << SCREEN_WIDTH << "x" << SCREEN_HEIGHT << "x" << SCREEN_HEIGHT << " OK" << endl;

	//SDL_EnableKeyRepeat(1, 1);

	/********************
	** game init stuff **
	********************/
	
	TTF_Font* fnt = TTF_OpenFont("data/fonts/ATWOOD.ttf", 18);
	
	level = new CLevel;
	if (argc > 1) {
		std::string str = args[1];
		level->loadDataFromFile("data/maps/"+str+".lvl");
		level->setLevel(atoi(str.c_str()));
	} else {
		level->loadDataFromFile("data/maps/1.lvl");	
		level->setLevel(1);
	}
	

	CBall *ball;
	ball = new CBall(level->getStartPoint());
	
	camera.setViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_W, VIEWPORT_H);
	/**************
	** game loop **
	**************/
	SDL_Event event;
	
	
	bool mouseDown = false;
	int mouseX = 0;
	int mouseY = 0;
	
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;
	bool introZoom = true;
	
	int32 loopStart = SDL_GetTicks();
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
						
						// do some shit based on the fact the mouse has been pressed
						if (ball->isRelPointInside(event.button.x, event.button.y) && ball->isStationary()) {
							ball->startFling(event.button.x, event.button.y);
						}
						
						
						mouseDown = true;
					}
					break;
					
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT) {
						if (ball->isFlinging()) {
							ball->stopFling(event.button.x, event.button.y);	// launch sucker!
						}
						mouseDown = false;
					}
					break;
								
				case SDL_MOUSEMOTION:
					mouseX = event.motion.x;
					mouseY = event.motion.y;
					break;
			}
		}
		
		if (keyPressed(SDLK_ESCAPE)) {
			quit = 1;
			break;
		}
		if (introZoom) {
			if (SDL_GetTicks() - loopStart >= 2500) {
				camera.zoomIn(0.25f);
				if (camera.getZoom() >= DEFAULT_METRES_TO_PIXELS) {
					camera.setZoom(DEFAULT_METRES_TO_PIXELS);
					introZoom = false;
				}
			}
		} else {
			if (keyPressed(SDLK_z)) {
				camera.zoomOut();
			} else if (keyPressed(SDLK_x)) {
				camera.zoomIn();
			}
		}
		
		/*********************
		** game logic stuff **
		*********************/
		level->world->Step(timeStep, iterations);
		
		if (ball->isAtGoal() && ball->isStationary()) {
			// hooray! level complete
			if (level->loadNextLevel()) {
				cout << ball->getFlings() << " " << ball->getBounces() << endl;
				ball->reset(level->getStartPoint());
				camera.setViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_W, VIEWPORT_H);
			}
		}
		
		if (ball->cameraX() < (VIEWPORT_X + CAMERA_MOVE_THRESHOLD)) {
			int ox = (VIEWPORT_X + CAMERA_MOVE_THRESHOLD) - ball->cameraX();
			camera.translate(ox, 0);
		} else if (ball->cameraX() > (VIEWPORT_W - CAMERA_MOVE_THRESHOLD)) {
			int ox = ball->cameraX() - (VIEWPORT_W - CAMERA_MOVE_THRESHOLD);
			camera.translate(-ox, 0);
		}
		
		if (ball->cameraY() < (VIEWPORT_Y + CAMERA_MOVE_THRESHOLD)) {
			int oy = (VIEWPORT_Y + CAMERA_MOVE_THRESHOLD) - ball->cameraY();
			camera.translate(0, oy);
		} else if (ball->cameraY() > (VIEWPORT_H - CAMERA_MOVE_THRESHOLD)) {
			int oy = ball->cameraY() - (VIEWPORT_H - CAMERA_MOVE_THRESHOLD);
			camera.translate(0, -oy);
		}
		
		
		/********************
		** rendering stuff **
		********************/
		
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));  // white layer
		
		
		level->render();
		ball->render();
		
		//sprintf(strBuffer, "Level: %s (%s)", level->getTitle().c_str(), level->getTimeSpentString().c_str());
		sprintf(strBuffer, "%s", level->getTitle().c_str());
		SDL_Color clrFg = {0,0,255,0};  // Blue ("Fg" is foreground)
		SDL_Surface *sText = TTF_RenderText_Solid( fnt, strBuffer, clrFg );
		SDL_Rect rcDest = {2,VIEWPORT_H-60,0,0};
		SDL_BlitSurface( sText,NULL, screen,&rcDest );
		SDL_FreeSurface( sText );
		
		sprintf(strBuffer, "Flings: %d", ball->getFlings());
		sText = TTF_RenderText_Solid( fnt, strBuffer, clrFg );
		rcDest.y = VIEWPORT_H-40;
		SDL_BlitSurface( sText,NULL, screen,&rcDest );
		
		if (ball->isFlinging()) {
			int x1 = ball->getFlingX();
			int y1 = ball->getFlingY();
			int x2 = mouseX;
			int y2 = mouseY;
			lineRGBA(screen, x1, y1, x2, y2, 128, 128, 255, 255);
			
			
			sprintf(strBuffer, "Power: %.0f%%", ball->getFlingStrength(mouseX, mouseY));
			sText = TTF_RenderText_Solid( fnt, strBuffer, clrFg );
			rcDest.y = VIEWPORT_H-20;
			SDL_BlitSurface( sText,NULL, screen,&rcDest );
			
		}
		
		SDL_FreeSurface( sText );
		
		SDL_Flip(screen);  // flip back buffer -> screen
		
		//SDL_framerateDelay(fpsman);
		
		frameTime = SDL_GetTicks()-startTime;
		fps = (frameTime>0) ? 1000 / frameTime : 0;
		SDL_Delay(16);
	}
	
	delete ball;
	delete level;
	TTF_CloseFont(fnt);
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
