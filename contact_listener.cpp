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
#include "data.h"

void ContactListener::Add(const b2ContactPoint* point) {
	CData* data1 = (CData*)point->shape1->GetUserData();
	CData* data2 = (CData*)point->shape2->GetUserData();
	
	if (data1 && data1->type == DATA_BALL) {
		data1->ball->addBounce();
		if (data2 && data2->type == DATA_END_POINT) {
			data1->ball->setAtGoal(true);
			data1->ball->setGoalTime();
		}
	} else if (data2 && data2->type == DATA_BALL) {
		data2->ball->addBounce();
		if (data1 && data1->type == DATA_END_POINT) {
			data2->ball->setAtGoal(true);
			data2->ball->setGoalTime();
		}
	}
}
 
void ContactListener::Persist(const b2ContactPoint* point) {
	CData* data1 = (CData*)point->shape1->GetUserData();
	CData* data2 = (CData*)point->shape2->GetUserData();
	
	if (data1 && data1->type == DATA_BALL) {
		data1->ball->doRollingSimulation();
	} else if (data2 && data2->type == DATA_BALL) {
		data2->ball->doRollingSimulation();
	}
}
 
void ContactListener::Remove(const b2ContactPoint* point) {
	CData* data1 = (CData*)point->shape1->GetUserData();
	CData* data2 = (CData*)point->shape2->GetUserData();
	if (data1 && data1->type == DATA_BALL) {
		data1->ball->setAtGoal(false);
	} else if (data2 && data2->type == DATA_BALL) {
		data2->ball->setAtGoal(false);
	}
}
 
void ContactListener::Result(const b2ContactResult* point) {
	// handle results
}
