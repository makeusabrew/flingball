//
// C++ Implementation: contact_listener
//
// Description: 
//
//
// Author: Nick Payne <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <sstream>
#include <iostream>
#include "globals.h"
#include "contact_listener.h"

void ContactListener::Add(const b2ContactPoint* point) {
	// handle add point
}
 
void ContactListener::Persist(const b2ContactPoint* point) {
	grounded = true;
}
 
void ContactListener::Remove(const b2ContactPoint* point) {
	grounded = false;
}
 
void ContactListener::Result(const b2ContactResult* point) {
	// handle results
}
