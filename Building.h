/*
 *  Building.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _BUILDING_PLN__H
#define _BUILDING_PLN__H

#include "LiftManager.h"

/*!
 @class
 @abstract    Represent a Building
 */


class Building {
public:
	int _nb_levels;
	int _nb_lifts;
	LiftManager *_lift_manager;
	
	
public:
	
	Building(int nb_levels, int nb_lifts);	
	~Building();
	void processNewEvent(const Man &m, int start, int end);	
	
	
};

#endif
