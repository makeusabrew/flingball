//
// C++ Implementation: camera
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "camera.h"
CCamera::CCamera() {
	x = y = 0;
	w = h = 0;
}

bool CCamera::setViewport(int cx, int cy, int cw, int ch) {
	x = cx;
	y = cy;
	w = cw;
	h = ch;
	return true;
}

bool CCamera::translate(int mx, int my) {
	x += mx;
	y += my;
	return true;
}

bool CCamera::translateTo(int nx, int ny) {
	x = nx;
	y = ny;
	return true;
}

int CCamera::x2r(int ax) {
	return ax + x;
}

int CCamera::y2r(int ay) {
	return ay + y;
}

int CCamera::x2a(int rx) {
	return rx - x;
}

int CCamera::y2a(int ry) {
	return ry - y;
}