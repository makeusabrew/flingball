//
// C++ Implementation: path
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <SDL/SDL_gfxPrimitives.h>
#include "path.h"
CPath::CPath() {
	length = 0;
}

void CPath::setColour(int c) {
	colour = c;
}

bool CPath::addPoint(int px, int py) {
	if (length >= 100) {
		return false;
	}
	points[length].x = px;
	points[length].y = py;
	length++;
	return true;
}

void CPath::render() {
	for (int i = 0; i < length-1; i++) {
		lineRGBA(screen, RVX(points[i].x), RVY(points[i].y), RVX(points[i+1].x), RVY(points[i+1].y), 0, 0, 0, 255);
	}
}