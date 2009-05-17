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

#include "level.h"

using namespace std;

CLevel::CLevel() {
	w = h = 0;
	x = y = 0;
	numPaths = 0;
}

CLevel::~CLevel() {
	if (numPaths) {
		delete [] paths;
	}
}

bool CLevel::loadDataFromFile(string file) {
	ifstream fin(file.c_str());  // for some reason we need the wierd c_str() conversion
	if (!fin.is_open()) {
		return false;
	}
	
	getline(fin, title);	// first line is title	
	fin >> w >> h;				// next is world max dimensions
	fin >> startX >> startY;	// ball start coordinates
	fin >> numPaths;
	paths = new CPath[numPaths];
	for (int j = 0; j < numPaths; j++) {
		int numPoints;
		fin >> numPoints;
		paths[j].createPoints(numPoints);
		for (int i = 0; i < numPoints; i++) {
			int px = 0;
			int py = 0;
			fin >> px >> py;
			paths[j].addPoint(px, py);
		}
	}

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
	for (int i = 0; i < numPaths; i++) {
		// just render each path
		paths[i].render();
	}
}

Point CLevel::getStartPoint() {
	Point p;
	p.x = startX;
	p.y = startY;
	return p;
}