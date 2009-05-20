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
	bodyDef.angularDamping = 0.75f;
	body = level->world->CreateBody(&bodyDef);
	
	b2CircleDef shapeDef;
	shapeDef.radius = r;
	//shapeDef.localPosition.Set(r/2.0f, r/2.0f);	// this basically means where is the X / Y offset. we make it the middle of the ball
	
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.2f;
	shapeDef.restitution = 0.5f;
	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();
}

CBall::~CBall() {
	// pony down
	body = NULL;
}

b2Body* CBall::getBody() {
	return body;
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

bool CBall::isRelPointInside(float px, float py) {
	b2Vec2 position = body->GetPosition();
	int dx = camera.x2r(position.x);
	int dy = camera.y2r(position.y);
	int dr = camera.m2p(r);
	
	float x1 = dx-dr;
	float y1 = dy-dr;
	float x2 = dx+dr;
	float y2 = dy+dr;
	
	if (px > x1 && px < x2 && py > y1 && py < y2) {
		return true;
	} else {
		return false;
	}
}

void CBall::setLinearVelocity(b2Vec2 v) {
	body->SetLinearVelocity(v);
}

void CBall::render() {
	
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
		
	int dx = camera.x2r(position.x);
	int dy = camera.y2r(position.y);
	int dr = camera.m2p(r);
	if (!flinging) {
		circleRGBA(screen, dx, dy, dr, 0, 0, 0, 255);
	} else {
		circleRGBA(screen, dx, dy, dr, 128, 10, 0, 255);
	}
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
	int dx = mx-fX;
	int dy = my-fY;
	float dist = sqrt((dx*dx) + (dy*dy));	// this is the absolute distance the mouse was dragged. work on it
	
	if (body->IsSleeping()) {
		body->WakeUp();
	}
	
	if (dist > 150) {
		dist = 150;
	}
	dist *= 0.15;
	
	b2Vec2 v;
	// okay, we need to work out which quadrant we're in
	// just work clockwise, taking into account a few exceptions
	if (dy > 0 && dx == 0) {	// straight up
		v.x = 0;
		v.y = dist;
	} else if (dy < 0 && dx == 0) {	// straight down
		v.x = 0;
		v.y = -dist;
	} else if (dx > 0 && dy == 0) {	// straight left
		v.x = dist;
		v.y = 0;
	} else if (dx < 0 && dy == 0) {	// straight right
		v.x = -dist;
		v.y = 0;
	} else if (dy > 0 && dx < 0) {	// bottom left of ball
		float a = (float)dy / (float)dx;
		a = atan(a);
		v.x = cos((a)) * dist;
		v.y = sin((a)) * dist;
	} else if (dy > 0 && dx > 0) {	// bottom right of ball
		float a = atan2(dy, dx);		
		v.x = -(cos((a)) * dist);
		v.y = -(sin((a)) * dist);
	}
	body->SetLinearVelocity(v);
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
	b2Vec2 position = body->GetPosition();
	return camera.x2r(position.x);
}

int CBall::cameraY() {
	b2Vec2 position = body->GetPosition();
	return camera.y2r(position.y);
}