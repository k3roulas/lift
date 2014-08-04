/*
 *  Threaded.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _THREADED_PLN__H
#define _THREADED_PLN__H

#include <pthread.h>
#include "citi_class.h"


/*!
 @class
 @abstract   Represent a Thread with mutex for synchronisation
 */
class Threaded {
protected:
	pthread_t _thread;
	pthread_cond_t _wait_cond;
	pthread_mutex_t _wait_mutex;
	
	virtual void startThread()=0;
	
public:
	Threaded();
};

#endif