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
		bool isRelPointInside(float, float);
		void render();
		bool setColour(int, int, int);
		void setCoords(b2Vec2 p);
		void startFling(int, int);
		void stopFling(int, int);
		
		void setLinearVelocity(b2Vec2);
		
		bool isFlinging();
		int getFlingX();
		int getFlingY();
		
		int cameraX();
		int cameraY();
		
		b2Body* getBody();
		
		bool isStationary();
		bool isAtGoal();
		
		void setAtGoal(bool);
		
		void reset(b2Vec2);
		
		void doRollingSimulation();
		
		int getBounces();
		int getFlings();
		
		void addBounce();

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
		
		bool atGoal;
		
		b2Body* body;
		
		int flings;
		int bounces;
		
#ifdef DEBUG
		b2Vec2 path[1024];
#endif
};
		
#endif