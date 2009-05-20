//
// C++ Implementation: level
//
// Description: 
//
//
// Author: Nick Payne <nick@kurai.co.uk>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <iostream>
#include <fstream>
#include <SDL/SDL_gfxPrimitives.h>

#include "level.h"
#include "camera.h"

using namespace std;

CLevel::CLevel() {
	w = h = 0;
	x = y = 0;
}

CLevel::~CLevel() {
	delete world;
}

bool CLevel::loadDataFromFile(string file) {
	ifstream fin(file.c_str());  // for some reason we need the wierd c_str() conversion
	if (!fin.is_open()) {
		return false;
	}
	getline(fin, title);    // first line is title  
	fin >> w >> h;                          // next is world max dimensions
	fin >> startX >> startY;        // ball start coordinates
	
	createWorld();
	

	fin.close();
	return true;
}

string CLevel::getTitle() {
	return title;
}

int CLevel::getLeftBound() {
	return (x);
}

int CLevel::getRightBound() {
	return (x + w);
}

int CLevel::getTopBound() {
	return (y);
}

int CLevel::getBottomBound() {
	return (y + h);
}

void CLevel::render() {
	// need to draw four lines representing our boundaries
	//lineRGBA(screen, camera.x2r(this->getLeftBound()), camera.y2r(this->getTopBound()), camera.x2r(this->getRightBound()), camera.y2r(this->getTopBound()), 0, 0, 0, 255);
	//lineRGBA(screen, camera.x2r(this->getRightBound()), camera.y2r(this->getTopBound()), camera.x2r(this->getRightBound()), camera.y2r(this->getBottomBound()), 0, 0, 0, 255);
	//lineRGBA(screen, camera.x2r(this->getRightBound()), camera.y2r(this->getBottomBound()), camera.x2r(this->getLeftBound()), camera.y2r(this->getBottomBound()), 0, 0, 0, 255);
	//lineRGBA(screen, camera.x2r(this->getLeftBound()), camera.y2r(this->getBottomBound()), camera.x2r(this->getLeftBound()), camera.y2r(this->getTopBound()), 0, 0, 0, 255);

	
	for (b2Shape* s = worldStaticBody->GetShapeList(); s; s = s->GetNext()) {
		b2PolygonShape* sh = (b2PolygonShape *)s;
		int count = sh->GetVertexCount();

		const b2Vec2* v = sh->GetVertices();
		for (int i = 0; i < count; i++) {
			int sx = m2p(v[i].x);
			int sy = m2p(v[i].y);
			int dx = 0;
			int dy = 0;
			if (i == count-1) {
				dx = m2p(v[0].x);
				dy = m2p(v[0].y);
			} else {
				dx = m2p(v[i+1].x);
				dy = m2p(v[i+1].y);
			}
			lineRGBA(screen, sx, sy, dx, dy, 0, 0, 0, 255);
		}
	}
	
}

b2Vec2 CLevel::getStartPoint() {
	b2Vec2 p;
	p.x = startX;
	p.y = startY;
	return p;
}

CPath* CLevel::getPaths() {
//	return paths;
	return NULL;
}

void CLevel::createWorld() {
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(getLeftBound() - 10.0f, getTopBound() - 10.0f);
	worldAABB.upperBound.Set(getRightBound() + 10.0f, getBottomBound() + 10.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, gravity, true);	// last param is doSleep
	
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 0.0f);
	worldStaticBody = world->CreateBody(&bodyDef);
	
	b2PolygonDef triangleDef;
	triangleDef.vertexCount = 3;
	triangleDef.vertices[0].Set(5.0f, 10.0f);
	triangleDef.vertices[1].Set(7.5f, 5.0f);
	triangleDef.vertices[2].Set(10.0f, 10.0f);	
	worldStaticBody->CreateShape(&triangleDef);
	
	b2PolygonDef floorDef;
	floorDef.vertexCount = 4;
	floorDef.friction = 0.3f;
	floorDef.vertices[0].Set(0.0f, 11.0f);
	floorDef.vertices[1].Set(15.0f, 11.0f);
	floorDef.vertices[2].Set(15.0f, 12.0f);
	floorDef.vertices[3].Set(0.0f, 12.0f);	
	worldStaticBody->CreateShape(&floorDef);
	
	floorDef.vertexCount = 4;
	floorDef.friction = 0.3f;
	floorDef.vertices[0].Set(1.0f, 9.0f);
	floorDef.vertices[1].Set(2.0f, 9.0f);
	floorDef.vertices[2].Set(2.0f, 10.9f);
	floorDef.vertices[3].Set(1.0f, 10.9f);	
	worldStaticBody->CreateShape(&floorDef);
}