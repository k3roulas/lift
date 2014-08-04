/*
 *  man.h
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MAN_PLN__H
#define _MAN_PLN__H

#include <string>
#include "citi_class.h"

class Man {
	string _name;
public:
	Man(string name);
	string getName() const;
};

#endif