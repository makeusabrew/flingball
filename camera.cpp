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
	scale = MIN_METRES_TO_PIXELS;
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

int CCamera::x2r(float32 ax) {
	return int(m2p(ax) + x);
}

int CCamera::y2r(float32 ay) {
	return int(m2p(ay) + y);
}

float32 CCamera::x2a(int rx) {
	return (p2m(rx - x));
}

float32 CCamera::y2a(int ry) {
	return (p2m(ry -y));
}

float32 CCamera::m2p(float32 p) {
	return (p * scale);
}

float32 CCamera::p2m(float32 p) {
	return ((float32)p / scale);
}

void CCamera::zoomIn() {
	if (++scale > MAX_METRES_TO_PIXELS) {
		scale = MAX_METRES_TO_PIXELS;
	}
}

void CCamera::zoomOut() {
	if (--scale < MIN_METRES_TO_PIXELS) {
		scale = MIN_METRES_TO_PIXELS;
	}
}

void CCamera::zoomIn(float32 z) {
	scale += z;
	if (scale > MAX_METRES_TO_PIXELS) {
		scale = MAX_METRES_TO_PIXELS;
	}
}

void CCamera::zoomOut(float32 z) {
	scale -= z;
	if (scale < MIN_METRES_TO_PIXELS) {
		scale = MIN_METRES_TO_PIXELS;
	}
}

float32 CCamera::getZoom() {
	return scale;
}

void CCamera::setZoom(float32 z) {
	scale = z;
}