/*
 *  Building.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Building.h"


Building::Building(int nb_levels, int nb_lifts) : _nb_levels(nb_levels), _nb_lifts(nb_lifts) {
		_lift_manager = new LiftManager(nb_levels, nb_lifts);	
	}
	
Building::~Building() {
		cout << "Destruction du building" << endl ;
		
	}
	
void Building::processNewEvent(const Man &m, int start, int end) {
		_lift_manager->processNewEvent(m, start, end);		
	}
	