/*
 *  LiftManager.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _LIFTMANAGER_PLN__H
#define _LIFTMANAGER_PLN__H

#include <deque.h>

#include "citi_class.h"

#include "Lift.h"
#include "Threaded.h"

/*!
 @class
 @abstract    Repesent a Threaded Lift
 @discussion  Receive message from LiftManager and process it
 */

class LiftManager : public Threaded {

	int _nb_levels;
	int _nb_lifts;
	vector<Lift*> _lifts;
	deque<Event*> _events_new;
	deque<Event*> _events_stand_by;
	
	// start thread
	void startThread();
	// main loop
	int start();
	// to start the main loop
	static void * liftManagerLoop(void *data);

	// trigger to process an event
	void refreshChecker();

	
	// add a new event to the new internal queue
	void addEvent(const Man &m, int start, int end);
	
	// process a new event
	void processNewEvent(Event *e);
	
	// process an existing event from stand by queue
	int processEvent(Event *e);
	
public:
	
	LiftManager(int nb_levels, int nb_lifts);
	~LiftManager();
	
	// a lift call this method at the end of the delivering
	// used to process stand by event
	void retryStandByEvent();

	// add a new event
	void processNewEvent(const Man &m, int start, int end);	
};


#endif

