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
#include <sstream>
#include <SDL/SDL_gfxPrimitives.h>

#include "level.h"
#include "camera.h"
#include "contact_listener.h"
#include "data.h"
using namespace std;

CLevel::CLevel() {
	w = h = 0;
	x = y = 0;
	cLevel = 0;
	cBody = 0;
	
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(10000.0f, 10000.0f);

	// Define the gravity vector.
	b2Vec2 gravity(0.0f, 10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(worldAABB, gravity, true);	// last param is doSleep
	
	world->SetContactListener(new ContactListener());
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
	
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 0.0f);
	worldStaticBody = world->CreateBody(&bodyDef);
	
	// now set up our extreme four walls
	
	// ceiling
	b2PolygonDef bounds;
	bounds.vertexCount = 4;
	bounds.friction = WORLD_BOUNDARY_FRICTION;
	bounds.vertices[0].Set(getLeftBound(), getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[1].Set(getRightBound(),getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[2].Set(getRightBound(),getTopBound());
	bounds.vertices[3].Set(getLeftBound(),getTopBound());
	worldStaticBody->CreateShape(&bounds);
	
	// left wall
	bounds.vertexCount = 4;
	bounds.friction = WORLD_BOUNDARY_FRICTION;
	bounds.vertices[0].Set(getLeftBound() - WORLD_BOUNDARY_THICKNESS, getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[1].Set(getLeftBound(), getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[2].Set(getLeftBound(),getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[3].Set(getLeftBound() - WORLD_BOUNDARY_THICKNESS,getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	worldStaticBody->CreateShape(&bounds);
	
	// right wall
	bounds.vertexCount = 4;
	bounds.friction = WORLD_BOUNDARY_FRICTION;
	bounds.vertices[0].Set(getRightBound(), getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[1].Set(getRightBound() + WORLD_BOUNDARY_THICKNESS, getTopBound() - WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[2].Set(getRightBound() + WORLD_BOUNDARY_THICKNESS,getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[3].Set(getRightBound(), getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	worldStaticBody->CreateShape(&bounds);
	
	// bottom wall
	bounds.vertexCount = 4;
	bounds.friction = WORLD_BOUNDARY_FRICTION;
	bounds.vertices[0].Set(getLeftBound(), getBottomBound());	// 0.2f at time of writing = 10px
	bounds.vertices[1].Set(getRightBound(),getBottomBound());
	bounds.vertices[2].Set(getRightBound(),getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	bounds.vertices[3].Set(getLeftBound(),getBottomBound() + WORLD_BOUNDARY_THICKNESS);
	worldStaticBody->CreateShape(&bounds);
	
	// now pony up the rest of the bodies!
	
	int numPolys = 0;
	fin >> numPolys;
	
	fin >> endShapeIndex;

	for (int i = 0; i < numPolys; i++) {
		int numVertices = 0;
		fin >> numVertices;
		
		b2PolygonDef shapeDef;
		shapeDef.vertexCount = numVertices;
		
		bool isStatic = true;	// eventually this will be read from file
		
		if (i == endShapeIndex) {
			CData* data = new CData();
			data->type = DATA_END_POINT;
			shapeDef.userData = data;
		}
		for (int j = 0; j < numVertices; j++) {
			float x;
			float y;
			fin >> x >> y;
			shapeDef.vertices[j].Set(x, y);
		}
		if (isStatic) {
			worldStaticBody->CreateShape(&shapeDef);
		} else {
			b2BodyDef bodyDef;
			bodyDef.position.Set(0.0f, 0.0f);
			bodyDef.isBullet = true;
			b2Body* body = world->CreateBody(&bodyDef);
			shapeDef.density = 1.0f;
			shapeDef.friction = 0.3f;
			body->CreateShape(&shapeDef);
			body->SetMassFromShapes();
		}	
	}

	fin.close();
	return true;
}

string CLevel::getTitle() {
	return title;
}

string CLevel::getTimeSpentString() {
	return "10 secs";
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
	int sIndex = 0;	
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		for (b2Shape* s = b->GetShapeList(); s; s = s->GetNext()) {
			CData* data = (CData*)s->GetUserData();	
			if (data && data->type == DATA_BALL) {
				continue;
			}
			b2PolygonShape* sh = (b2PolygonShape *)s;
			int count = sh->GetVertexCount();
	
			const b2Vec2* v = sh->GetVertices();
			
			b2Vec2 o = b->GetPosition();
			//float32 a = b->GetAngle();
			for (int i = 0; i < count; i++) {
				int sx = camera.x2r(o.x + v[i].x);
				int sy = camera.y2r(o.y + v[i].y);
				int dx = 0;
				int dy = 0;
				if (i == count-1) {
					dx = camera.x2r(o.x + v[0].x);
					dy = camera.y2r(o.y + v[0].y);
				} else {
					dx = camera.x2r(o.x + v[i+1].x);
					dy = camera.y2r(o.y + v[i+1].y);
				}
				//if (i == endShapeIndex) {
				//	lineRGBA(screen, sx, sy, dx, dy, 0, 0, 255, 255);
				//} else {
					lineRGBA(screen, sx, sy, dx, dy, 0, 0, 0, 255);
				//}
			}
			sIndex++;	// bump up the index
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
	// deprecated
}

void CLevel::setLevel(int l) {
	cLevel = l;
}

int CLevel::getLevel() {
	return cLevel;
}

bool CLevel::loadNextLevel() {
	cLevel ++;
	std::ostringstream osstream;
	osstream << cLevel;
	std::string string = osstream.str();
	
	/*
	b2Body* node = world->GetBodyList();
	while (node) {
		b2Body* b = node;
		node = node->GetNext();
		b2Shape* s = b->GetShapeList();
		CData* data = (CData*)s->GetUserData();	
		if (data && data->type == DATA_BALL) {
			continue;
		}
		world->DestroyBody(b);
	}
	*/
	world->DestroyBody(worldStaticBody);
	worldStaticBody = NULL;
	// load the next level
	loadDataFromFile("data/maps/"+string+".lvl");
	return true;
}