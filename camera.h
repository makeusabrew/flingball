//
// C++ Interface: camera
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_CAMERA_H
#define INC_CAMERA_H
#include "globals.h"

class CCamera {
	public:
		CCamera();
		bool setViewport(int, int, int, int);
		
		bool translate(int, int);
		bool translateTo(int, int);
		
		int x2r(float32);
		int y2r(float32);
		
		int x2a(float32);
		int y2a(float32);
		
		float32 m2p(float32);
		float32 p2m(float32);
		
	private:
		int x;
		int y;
		
		int w;
		int h;
};

#endif