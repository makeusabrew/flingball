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
}

CBall::~CBall() {
	// pony down
}

bool CBall::isPointInside(float px, float py) {
	return false;
}

void CBall::draw(SDL_Surface *screen) {
	circleRGBA(screen, int(x), int(y), r, 0, 0, 0, 255);
}

void CBall::move() {
	vy += 0.2;
	if (vy > 20) {
		vy = 20;
	}
	
	x += vx;
	y += vy;
	
	if (y + r > SCREEN_HEIGHT) {
		y = SCREEN_HEIGHT - r;
		vy *= 0.8;
		vy = -vy;
	}

	if (x + r > SCREEN_WIDTH) {
		x = SCREEN_WIDTH - r;
		vx = -vx;
	} else if (x - r < 0) {
		x = 0 + r;
		vx = -vx;
	}
}