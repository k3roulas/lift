/*
 *  Threaded.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Threaded.h"

Threaded::Threaded() {
		pthread_mutex_init( &_wait_mutex, NULL);
		pthread_cond_init( &_wait_cond, NULL);	
	}