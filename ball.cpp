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
#include "ball.h"
#include "globals.h"
#include <SDL/SDL_gfxPrimitives.h>
CBall::CBall() {
	// pony up
	r = 16;
	x = 100;
	y = 100;
	vx = 3;
	vy = 0;
	cr = cg = cb = 0;
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
		
	x += vx;
	y += vy;
	
	if (y + r > level->getBottomBound()) {
		y = level->getBottomBound() - r;
		vy *= 0.8;
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
	if (vy > 20) {
		vy = 20;
	}
}

bool CBall::setColour(int r, int g, int b) {
	cr = r;
	cg = g;
	cb = b;
	return true;
}

void CBall::setCoords(int nx, int ny) {
	x = nx;
	y = ny;
}