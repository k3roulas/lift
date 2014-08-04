/*
 *  man.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "man.h"

Man::Man(string name) : _name(name) {}

string Man::getName() const { return _name; }