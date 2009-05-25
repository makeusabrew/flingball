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
#ifndef INC_LEVEL_H
#define INC_LEVEL_H

#include <string>
#include "path.h"

class CLevel {
	public:
		CLevel();
		~CLevel();
		bool loadDataFromFile(std::string);
		std::string getTitle();
		void render();
		int getLeftBound();
		int getRightBound();
		int getTopBound();
		int getBottomBound();
		b2Vec2 getStartPoint();
		CPath *getPaths();
		void createWorld();
		
		void setLevel(int);
		int getLevel();
		
		bool loadNextLevel();
		
		std::string getTimeSpentString();
		
		b2World *world;
		
	private:
		int data;
		int w;
		int h;
		int endShapeIndex;
		
		int cLevel;
		
		int timeStart;	// milliseconds
		
		float32 x;
		float32 y;
		float32 startX;
		float32 startY;
		std::string title;
		
		b2Body *worldStaticBody;
};
#endif