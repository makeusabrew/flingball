//
// C++ Interface: ball
//
// Description: 
//
//
// Author: Nick Payne <nick@kurai.co.uk>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef INC_LEVEL_H
#define INC_LEVEL_H

#include <string>

class CLevel {
	public:
		bool loadDataFromFile(std::string);
		std::string getTitle();
	private:
		int data;
		std::string title;
};

#endif