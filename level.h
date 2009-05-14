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
		bool loadDataFromFile(std::string);
		std::string getTitle();
		void render();
		int getLeftBound();
		int getRightBound();
		int getTopBound();
		int getBottomBound();
	private:
		int data;
		int w;
		int h;
		int x;
		int y;
		std::string title;
		int numPaths;
		CPath paths[100];
};
#endif