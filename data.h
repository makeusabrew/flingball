//
// C++ Interface: data
//
// Description: 
//
//
// Author: Nick <>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_DATA_H
#define INC_DATA_H
#include "ball.h"

class CData {
	public:
		CData();
		int type;
		CBall* ball;
};

#endif