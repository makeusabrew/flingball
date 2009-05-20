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
#include "level.h"
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

CBall::CBall(b2Vec2 p) {
	// pony up
	r = 0.32f;
	x = 0;
	y = 0;
	vx = 0;
	vy = 0;
	cr = cg = cb = 0;
	flinging = false;
	
	b2BodyDef bodyDef;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.userData = this;
	body = level->world->CreateBody(&bodyDef);
	
	b2CircleDef shapeDef;
	shapeDef.radius = r;
	//shapeDef.localPosition.Set(r/2.0f, r/2.0f);	// this basically means where is the X / Y offset. we make it the middle of the ball
	
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.5f;
	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();
}

CBall::~CBall() {
	// pony down
	body = NULL;
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
	//int dx = this->cameraX();
	//int dy = this->cameraY();
	//circleRGBA(screen, dx, dy, r, cr, cg, cb, 255);
	
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
		
	int dx = m2p(position.x);
	int dy = m2p(position.y);
	int dr = m2p(r);
	circleRGBA(screen, dx, dy, dr, 0, 0, 0, 255);
	
	int lx = dx - cos((angle)) * dr;
	int ly = dy - sin((angle)) * dr;
	
	int lx2 = dx + cos((angle)) * dr;
	int ly2 = dy + sin((angle)) * dr;
	
	lineRGBA(screen, lx, ly, lx2, ly2, 0, 0, 0, 255);
}

bool CBall::setColour(int r, int g, int b) {
	cr = r;
	cg = g;
	cb = b;
	return true;
}

void CBall::setCoords(b2Vec2 p) {
	//bodyDef.position.Set(p.x, p.y);
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