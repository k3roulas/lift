/*
 *  Event.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _EVENT_PLN__H
#define _EVENT_PLN__H

#include "citi_class.h"


/*!
 @class
 @abstract    Represent an Event : a man who want to go from level start to level end
 */
class Event  {
	const Man& _man;
	int _start;
	int _end;
	int _in_process; // 0 : wait, 1: in process
public:
	Event(const Man &m, int start, int end);
	const Man & getMan();
	int getStart();
	int getEnd();
	int isEventUp();
	int isInProcess();
	void setInProcess();
};

#endif 