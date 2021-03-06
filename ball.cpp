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
#include "data.h"
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
	flings = bounces = 0;
	flinging = false;
	atGoal = false;
	
	CData* data = new CData();
	data->type = DATA_BALL;
	data->ball = this;
	
	b2BodyDef bodyDef;
	bodyDef.position.Set(p.x, p.y);
	bodyDef.angularDamping = 0.1f;
	body = level->world->CreateBody(&bodyDef);
	
	b2CircleDef shapeDef;
	shapeDef.radius = r;
	
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	shapeDef.restitution = 0.6f;
	shapeDef.userData = data;
	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();
}

void CBall::reset(b2Vec2 p) {
	b2Vec2 v;
	v.x = 0;
	v.y = 0;
	body->SetXForm(p, 0.0f);
	body->SetLinearVelocity(v);
	body->SetAngularVelocity(0.0f);
	flings = 0;
	bounces = 0;
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
		
	float32 dx = camera.x2r(position.x);
	float32 dy = camera.y2r(position.y);
	float32 dr = camera.m2p(r);

	circleRGBA(screen, dx, dy, dr, 0, 0, 0, 255);
	
	float32 lx = dx - (cos(angle) * dr);
	float32 ly = dy - (sin(angle) * dr);
	
	float32 lx2 = dx + (cos(angle) * dr);
	float32 ly2 = dy + (sin(angle) * dr);
	
	lineRGBA(screen, (int)lx, (int)ly, (int)lx2, (int)ly2, 0, 0, 0, 255);
	
	float32 oangle = angle - (deg2rad(90.0f));
	
	lx = dx - (cos(oangle) * dr);
	ly = dy - (sin(oangle) * dr);
	
	lx2 = dx + (cos(oangle) * dr);
	ly2 = dy + (sin(oangle) * dr);
	
	lineRGBA(screen, (int)lx, (int)ly, (int)lx2, (int)ly2, 0, 0, 0, 255);
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

float CBall::getFlingStrength(int mx, int my) {
	int dx = mx-fX;
	int dy = my-fY;
	float dist = sqrt((dx*dx) + (dy*dy));	// this is the absolute distance the mouse was dragged. work on it
	
	if (dist > MAX_FLING_DRAG) {
		dist = MAX_FLING_DRAG;
	}
	
	float pc = (dist / MAX_FLING_DRAG) * 100.0f;
	return pc;
}

void CBall::stopFling(int mx, int my) {
	int dx = mx-fX;
	int dy = my-fY;
	float dist = sqrt((dx*dx) + (dy*dy));	// this is the absolute distance the mouse was dragged. work on it
	
	if (body->IsSleeping()) {
		body->WakeUp();
	}
	
	if (dist > MAX_FLING_DRAG) {
		dist = MAX_FLING_DRAG;
	}
	dist *= 0.15;
	
	b2Vec2 v;
	float32 av = 0.0f;
	b2Vec2 position = body->GetPosition();
	av = (camera.x2a(fX) - position.x)*100;
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
		v.x = cos(a) * dist;
		v.y = sin(a) * dist;		
	} else if (dy > 0 && dx > 0) {	// bottom right of ball
		float a = atan2(dy, dx);		
		v.x = -(cos(a) * dist);
		v.y = -(sin(a) * dist);
	}
	body->SetLinearVelocity(v);
	body->SetAngularVelocity(av);
	flinging = false;
	flings ++;
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

bool CBall::isStationary() {
	b2Vec2 v = body->GetLinearVelocity();
	if (abs(v.x) < 0.05 && abs(v.y) < 0.05) {
		return true;
	}
	return false;
}

float CBall::distFromGoal() {
	b2Vec2 p = body->GetPosition();
	b2Vec2 l = level->getEndPosition();
	float dx = p.x - l.x;
	float dy = p.y - l.y;
	float dist = sqrt((dx*dx) + (dy*dy));
	return dist;
}

void CBall::setAtGoal(bool goal) {
	atGoal = goal;
}

void CBall::setGoalTime() {
	goalTime = SDL_GetTicks();
}

unsigned int CBall::timeAtGoal() {
	return SDL_GetTicks() - goalTime;
}

bool CBall::isAtGoal() {
	return atGoal;
}

void CBall::doRollingSimulation() {
	float32 v = body->GetAngularVelocity();
	if (v > 0) {
		v -= BALL_ROLLING_FRICTION;
	} else if (v < 0) {
		v += BALL_ROLLING_FRICTION;
	}
	if (abs(v) <= BALL_ROLLING_FRICTION) {
		v = 0.0f;
	}
	body->SetAngularVelocity(v);
}

void CBall::addBounce() {
	bounces ++;
}

int CBall::getBounces() {
	return bounces;
}

int CBall::getFlings() {
	return flings;
}