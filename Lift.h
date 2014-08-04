/*
 *  Lift.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _LIFT_PLN__H
#define _LIFT_PLN__H

#include <pthread.h>
#include <set.h>
#include <vector.h>

#include "citi_class.h"
#include "Event.h"
#include "Threaded.h"

class LiftManager;

class Lift : public Threaded {
protected:
	int _id;
	LiftManager *_lift_manager;
	
	int _direction; // 0 stop, 1 up, 2 down
	int _position;
	int _routing_level;
	int _state;	// 0 routing : peut prendre des passagers selement sur le trajet (pas au delas)	
	            // 1 dessert : peut prendre des passagers sur le trajet et au delas.
	
	set<int> _level_to_process;
	vector<Event *> _events; 
	
	// start thread
	void startThread();
	// main loop
	int start();
	// to call the man loop
	static void * liftLoop(void *data);
	
	// during the move, initialise the direction if needed
	void initDirection();
	// after the move, deliver man in the level if needed
	void deliver();
	// after the move, board in man, if needed
	void boardIn();
	
public:
	
	Lift(LiftManager *lift_manager, int id);	
	~Lift();
	
	// move to the next level
	void nextMove();
	
	// add a routing event in the vector and init lift for the next move
	void addRoutingEvent(Event *e);	
	
	// add an event in the vector and init lift for the next move
	void addEvent(Event *e);
	
	// ask to the lift to check if there is a new event to process
	void refreshChecker();	
	void Print();
	
	// switch in routing mode
	void setRouting();
	// switch in delivering mode
	void setDelivering();
	
	
	int isRouting();
	int getPosition();
	void setStandBy();
	int isStandBy();
	int isUp();
	int isDown();
	void setUp();	
	void setDown();	
	void setRoutingLevel(int level);	
	int getRoutingLevel();
};

#endif