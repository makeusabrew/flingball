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
		Point getStartPoint();
		CPath *getPaths();
		int getNumPaths();
	private:
		int data;
		int w;
		int h;
		int x;
		int y;
		int startX;
		int startY;
		std::string title;
		int numPaths;
		CPath* paths;
};
#endif