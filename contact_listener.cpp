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
#include "contact_listener.h"

void ContactListener::Add(const b2ContactPoint* point) {
	// handle add point
}
 
void ContactListener::Persist(const b2ContactPoint* point) {
	std::cout << "persist" << std::endl;
}
 
void ContactListener::Remove(const b2ContactPoint* point) {
	std::cout << "remove" << std::endl;
}
 
void ContactListener::Result(const b2ContactResult* point) {
	// handle results
}
