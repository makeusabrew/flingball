//
// C++ Interface: path
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_PATH_H
#define INC_PATH_H
#include <SDL/SDL.h>
#include "globals.h"

class CPath {
	public:
		CPath();
		~CPath();
		void setColour(int);
		bool addPoint(float32, float32);
		bool addRelPoint(int, int);
		void render();
		bool isPolygon();
		bool createPoints(int);
		void lineToPoint(int, int);
		void renderLastPoint();
		Point getPoint(int);
		int getLength();
		bool isValid();
		std::string getValidationError();
		void renderHalos();
		void moveToRelPoint(int, int);
		bool isPointCenter(int, int);
		int isPointInVertex(int, int);
		void moveVertexToRelPoint(int, int, int);
		void redoBounds();
	private:
		int colour;
		int length;	// number of points
		int cPoint;
		Point points[32];
		std::string strErr;
		float32 left;
		float32 right;
		float32 top;
		float32 bottom;
};

#endif