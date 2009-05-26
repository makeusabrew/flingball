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
	top = 999999;
	left = 999999;
	bottom = -999999;
	right = -999999;
	strErr = "";
}

CPath::~CPath() {
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

bool CPath::addRelPoint(int px, int py) {
	return addPoint(camera.x2a(px), camera.y2a(py));
}

bool CPath::addPoint(float32 px, float32 py) {
	
	length ++;
	cPoint = length-1;
	points[cPoint].x = px;
	points[cPoint].y = py;
	
	redoBounds();
	
	
	std::cout << "added new vertex (" << cPoint << ") at " << points[cPoint].x << " " << points[cPoint].y << std::endl;
	return true;
}

int CPath::getLength() {
	return length;
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
	if (length >= 2) {
		for (int i = 0; i < length-1; i++) {
			lineRGBA(screen, camera.x2r(points[i].x), camera.y2r(points[i].y), camera.x2r(points[i+1].x), camera.y2r(points[i+1].y), 0, 0, 0, 255);
			//std::cout << "line " << camera.x2r(points[i].x) << " " << camera.x2r(points[i].y) << " -> " << camera.x2r(points[i+1].x) << camera.x2r(points[i+1].y) << std::endl;
		}
	}
}

void CPath::lineToPoint(int px, int py) {
	if (length) {
		lineRGBA(screen, camera.x2r(points[length-1].x), camera.y2r(points[length-1].y), px, py, 0, 0, 0, 255);
	}
}

void CPath::renderHalos() {
	if (length) {
		float32 r = 0.16f;
		for (int i = 0; i < length; i++) {
			circleRGBA(screen, camera.x2r(points[i].x), camera.y2r(points[i].y), camera.m2p(r), 255, 0, 0, 255);
		}
		float32 mx = left + ((right-left)/2.0);
		float32 my = top + ((bottom-top)/2.0);
		circleRGBA(screen, camera.x2r(mx), camera.y2r(my), camera.m2p(0.25f), 255, 0, 0, 255);
	}
}

void CPath::renderLastPoint() {
	lineRGBA(screen, camera.x2r(points[length-1].x), camera.y2r(points[length-1].y), camera.x2r(points[0].x), camera.y2r(points[0].y), 0, 0, 0, 255);
}

std::string CPath::getValidationError() {
	return strErr;
}

bool CPath::isValid() {
	if (length < 3) {
		strErr = "Too few points";
		return false;
	}
	return true;
}

void CPath::moveToRelPoint(int nx, int ny) {
	float32 ax = camera.x2a(nx);
	float32 ay = camera.y2a(ny);
	
	float32 mx = left + ((right-left)/2.0);
	float32 my = top + ((bottom-top)/2.0);
	
	float32 dx = ax - mx;
	float32 dy = ay - my;
	for (int i = 0; i < getLength(); i++) {
		points[i].x += dx;
		points[i].y += dy;
	}
	left += dx;
	right += dx;
	
	top += dy;
	bottom += dy;
}

bool CPath::isPointCenter(int nx, int ny) {
	
	float32 ax = camera.x2a(nx);
	float32 ay = camera.y2a(ny);
	
	float32 mx = left + ((right-left)/2.0);
	float32 my = top + ((bottom-top)/2.0);
	float32 tolerance = 0.25f;
	if (ax > (mx - tolerance) && ax < (mx + tolerance) &&	ay > (my - tolerance) && ay < (my + tolerance)) {
		return true;
	}
	return false;
}

int CPath::isPointInVertex(int nx, int ny) {
	
	float32 ax = camera.x2a(nx);
	float32 ay = camera.y2a(ny);	
	
	float32 tolerance = 0.16f;
	
	for (int i = 0; i < length; i++ ) {
		float32 mx = points[i].x;
		float32 my = points[i].y;
		if (ax > (mx - tolerance) && ax < (mx + tolerance) &&	ay > (my - tolerance) && ay < (my + tolerance)) {
			return i;
		}
	}
	return -1;
}

void CPath::moveVertexToRelPoint(int i, int nx, int ny) {
	float32 ax = camera.x2a(nx);
	float32 ay = camera.y2a(ny);	
	
	float32 mx = points[i].x;
	float32 my = points[i].y;
	
	float32 dx = ax - mx;
	float32 dy = ay - my;
	
	points[i].x += dx;
	points[i].y += dy;
	
	redoBounds();
}

void CPath::redoBounds() {
	top = 999999;
	left = 999999;
	bottom = -999999;
	right = -999999;
	
	for (int i = 0; i < length; i++) {
		float32 px = points[i].x;
		float32 py = points[i].y;
		
		if (px < left) {
			left = px;
		}
		if (px > right) {
			right = px;
		}
		if (py < top) {
			top = py;
		}
		if (py > bottom) {
			bottom = py;
		}
	}
}