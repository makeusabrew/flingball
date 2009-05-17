//
// C++ Implementation: ball
//
// Description: 
//
//
// Author: Nick Payne <nick@kurai.co.uk>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <sstream>
#include <iostream>
#include "ball.h"
#include "globals.h"
#include "camera.h"
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

CBall::CBall() {
	// pony up
	r = 16;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	cr = cg = cb = 0;
	flinging = false;
}

CBall::~CBall() {
	// pony down
}

bool CBall::isPointInside(float px, float py) {
	float x1 = x-r;
	float y1 = y-r;
	float x2 = x+r;
	float y2 = y+r;
	
	if (px > x1 && px < x2 && py > y1 && py < y2) {
		return true;
	} else {
		return false;
	}
}

void CBall::render() {
	int dx = this->cameraX();
	int dy = this->cameraY();
	circleRGBA(screen, dx, dy, r, cr, cg, cb, 255);
}

void CBall::move(CLevel *level) {
	
	if (vy > 20) {
		vy = 20;
	} else if (vy < -20) {
		vy = -20;
	}
		
	x += vx;
	y += vy;
	
	if (y + r > level->getBottomBound()) {
		y = level->getBottomBound() - r;
		vy *= 0.65;
		vy = -vy;
	}	else if (y - r < level->getTopBound()) {
		y = level->getTopBound() + r;
		vy *= 0.65;
		vy = -vy;
	}

	if (x + r > level->getRightBound()) {
		x = level->getRightBound() - r;
		vx *= 0.8;
		vx = -vx;
	} else if (x - r < level->getLeftBound()) {
		x = level->getLeftBound() + r;
		vx *= 0.8;
		vx = -vx;
	}
	
	vy += 0.2;
	
	if (abs((y+r) - level->getBottomBound()) < 0.1) {
		// consider this grounded
		if (vx > 0) {
			vx -= 0.1;
		} else if (vx < 0) {
			vx += 0.1;
		}
	} else {
		// airborne
		if (vx > 0) {
			vx -= 0.005;
		} else if (vx < 0) {
			vx += 0.005;
		}
	}
	
	
	CPath *paths = level->getPaths();
	int numPaths = level->getNumPaths();
	
#ifdef DEBUG
	this->setColour(0, 0, 0);
#endif
	for (int i = 0; i < numPaths; i++) {
		// first of all, are we making contact at all?
		int x1 = (int)x - r;
		int y1 = (int)y - r;
		int x2 = (int)x + r;
		int y2 = (int)y + r;
		
		Point min = paths[i].getMinPoint();
		Point max = paths[i].getMaxPoint();
		
		if (!(x1 > max.x || x2 < min.x ||
				y1 > max.y || y2 < min.y)) {
			// we intersect with this object
#ifdef DEBUG
			this->setColour(0, 0, 255);
#endif
			// the following is completely wrong. it's just a (bad) start
			// we need to detect which edge crossed into the path
			// hmm. stumped
		}

	}
	
	if (abs(vx) < 0.1) {
		vx = 0;
	}
	
}

bool CBall::setColour(int r, int g, int b) {
	cr = r;
	cg = g;
	cb = b;
	return true;
}

void CBall::setCoords(Point p) {
	x = p.x;
	y = p.y;
}

void CBall::startFling(int mx, int my) {
	fX = mx;
	fY = my;
	flinging = true;
}

//Ian was ear.

void CBall::stopFling(int mx, int my) {
	float dx = mx-fX;
	float dy = my-fY;
	float dist = sqrt((dx*dx) + (dy*dy));	// this is the absolute distance the mouse was dragged. work on it
	
	if (dist > 150) {
		dist = 150;
	}
	dist *= 0.15;
	
	float a = dy / dx;
	a = atan(a);
	
	vx = cos((a)) * dist;
	vy = sin((a)) * dist;
	flinging = false;
}

bool CBall::isFlinging() {
	return flinging;
}

int CBall::getFlingX() {
	return fX;
}

int CBall::getFlingY() {
	return fY;
}

int CBall::cameraX() {
	return camera.x2r(int(x));
}

int CBall::cameraY() {
	return camera.y2r(int(y));
}