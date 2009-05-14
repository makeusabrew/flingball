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
	return false;
}

void CBall::render() {
	int dx = int(x) + VIEWPORT_X;
	int dy = int(y) + VIEWPORT_Y;
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
	}

	if (x + r > level->getRightBound()) {
		x = level->getRightBound() - r;
		vx = -vx;
	} else if (x - r < level->getLeftBound()) {
		x = level->getLeftBound() + r;
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

void CBall::stopFling(int mx, int my) {
	float dx = mx-fX;
	float dy = my-fY;
	float dist = sqrt((dx*dx) + (dy*dy));	// this is the absolute distance the mouse was dragged. work on it
	
	if (dist > 100) {
		dist = 100;
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