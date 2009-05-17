//
// C++ Implementation: camera
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "camera.h"
CCamera::CCamera() {
	x = y = 0;
	w = h = 0;
}

bool CCamera::setViewport(int cx, int cy, int cw, int ch) {
	x = cx;
	y = cy;
	w = cw;
	h = ch;
	return true;
}