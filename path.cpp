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
#include <iostream>
#include <SDL/SDL_gfxPrimitives.h>
#include "path.h"
#include "camera.h"
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
	
	points[cPoint].x = camera.x2a(px);
	points[cPoint].y = camera.y2a(py);
	
	
	std::cout << "added new vertex at " << points[cPoint].x << " " << points[cPoint].y << std::endl;
	cPoint++;
	return true;
}

int CPath::getLength() {
	return cPoint + 1;
}

Point CPath::getPoint(int i) {
	return points[i];
}
	

void CPath::render() {
	/*
#ifdef DEBUG
	lineRGBA(screen, camera.x2r(min.x), camera.y2r(min.y), camera.x2r(min.x), camera.y2r(max.y), 128, 255, 0, 255);
	lineRGBA(screen, camera.x2r(min.x), camera.y2r(min.y), camera.x2r(max.x), camera.y2r(min.y), 128, 255, 0, 255);
	lineRGBA(screen, camera.x2r(min.x), camera.y2r(max.y), camera.x2r(max.x), camera.y2r(max.y), 128, 255, 0, 255);
	lineRGBA(screen, camera.x2r(max.x), camera.y2r(max.y), camera.x2r(max.x), camera.y2r(min.y), 128, 255, 0, 255);
#endif
	*/
	if (cPoint >= 1) {
		for (int i = 0; i < cPoint-1; i++) {
			lineRGBA(screen, camera.x2r(points[i].x), camera.y2r(points[i].y), camera.x2r(points[i+1].x), camera.y2r(points[i+1].y), 0, 0, 0, 255);
			//std::cout << "line " << camera.x2r(points[i].x) << " " << camera.x2r(points[i].y) << " -> " << camera.x2r(points[i+1].x) << camera.x2r(points[i+1].y) << std::endl;
		}
	}
}

void CPath::lineToPoint(int px, int py) {
	if (cPoint > 0) {
		lineRGBA(screen, camera.x2r(points[cPoint-1].x), camera.y2r(points[cPoint-1].y), px, py, 0, 0, 0, 255);
	}
}

Point CPath::getMinPoint() {
	return min;
}

Point CPath::getMaxPoint() {
	return max;
}

void CPath::renderLastPoint() {
	lineRGBA(screen, camera.x2r(points[cPoint-1].x), camera.y2r(points[cPoint-1].y), camera.x2r(points[0].x), camera.y2r(points[0].y), 0, 0, 0, 255);
}