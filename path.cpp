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
	cPoint = length = 0;
	// we use the values below as they are "extremes" we're not going to encounter
	// in a real level. We could replace this with a #defined constant if we want
	min.x = 999999;
	min.y = 999999;
	max.x = -999999;
	max.y = -999999;
}

CPath::~CPath() {
	if (length) {
		delete [] points;
	}
}

void CPath::setColour(int c) {
	colour = c;
}

bool CPath::isPolygon() {
	// this checks if the points on this path join up to form a polygon
	return ((length > 2) && 
			(points[0].x == points[length-1].x) &&
			(points[0].y == points[length-1].y));
}

bool CPath::createPoints(int num) {
	length = num;
	points = new Point[num];
	return true;
}

bool CPath::addPoint(int px, int py) {
	// check if this is outside our current bounding box
	if (px < min.x) {
		min.x = px;
	}
	if (py < min.y) {
		min.y = py;
	}
	if (px > max.x) {
		max.x = px;
	}
	if (py > max.y) {
		max.y = py;
	}
	
	points[cPoint].x = px;
	points[cPoint].y = py;
	cPoint++;
	return true;
}

void CPath::render() {
#ifdef DEBUG
	lineRGBA(screen, RVX(min.x), RVY(min.y), RVX(min.x), RVY(max.y), 128, 255, 0, 255);
	lineRGBA(screen, RVX(min.x), RVY(min.y), RVX(max.x), RVY(min.y), 128, 255, 0, 255);
	lineRGBA(screen, RVX(min.x), RVY(max.y), RVX(max.x), RVY(max.y), 128, 255, 0, 255);
	lineRGBA(screen, RVX(max.x), RVY(max.y), RVX(max.x), RVY(min.y), 128, 255, 0, 255);
#endif
	for (int i = 0; i < length-1; i++) {
		lineRGBA(screen, RVX(points[i].x), RVY(points[i].y), RVX(points[i+1].x), RVY(points[i+1].y), 0, 0, 0, 255);
	}
}