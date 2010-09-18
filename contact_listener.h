//
// C++ Interface: contact_listener
//
// Description: 
//
//
// Author: Nick Payne <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_CONTACT_LISTENER_H
#define INC_CONTACT_LISTENER_H

#include "Include/Box2D.h"

class ContactListener : public b2ContactListener {
	public:
		void Add(const b2ContactPoint* point); 
		void Persist(const b2ContactPoint* point); 
		void Remove(const b2ContactPoint* point); 
		void Result(const b2ContactResult* point);
};

#endif