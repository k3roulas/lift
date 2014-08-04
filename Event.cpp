/*
 *  Event.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Event.h"


Event::Event(const Man &m, int start, int end) : _man(m), _start(start), _end(end), _in_process(0) {}
const Man & Event::getMan() {return _man;}
int Event::getStart() { return _start; }
int Event::getEnd() { return _end; }
int Event::isEventUp() { return (_end - _start > 0); }
int Event::isInProcess() { return _in_process == 0; }
void Event::setInProcess() { _in_process == 1; }
