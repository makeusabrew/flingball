//
// C++ Interface: ball
//
// Description: 
//
//
// Author: Nick Payne <nick@kurai.co.uk>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_BALL_H
#define INC_BALL_H
#include <SDL/SDL.h>
#include "globals.h"

class CBall {
	public:
		CBall(b2Vec2);
		~CBall();
		bool isPointInside(float px, float py);
		void render();
		bool setColour(int, int, int);
		void setCoords(b2Vec2 p);
		void startFling(int, int);
		void stopFling(int, int);
		
		bool isFlinging();
		int getFlingX();
		int getFlingY();
		
		int cameraX();
		int cameraY();

	private:
		float x;
		float y;

		float vx;
		float vy;

		float32 r;
		
		int cr;
		int cg;
		int cb;
		
		bool flinging;	// dragging a fling?
		int fX;	// fling X
		int fY;	// fling Y
		
		b2Body* body;
};
		
#endif