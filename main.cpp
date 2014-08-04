#include <iostream>
#include <string>
#include <pthread.h>
#include <deque.h>
#include <set.h>
#include <list.h>
#include <vector.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std ;


#include "Man.h"
#include "Building.h"


int main (int argc, char * const argv[]) {
	
	int nb_level = 10;
	int nb_lifts = 1;
	Building building(nb_level, nb_lifts);
	Man pierre("Pierre"), robert("Robert"), yolande("Yolande"), anne("Anne"), olivier("Olivier");
	
	sleep(1);
	building.processNewEvent(pierre, 2, 5);
	sleep(1);
	building.processNewEvent(robert, 3, 10);

					
	sleep(15);
	

	
	
	
	return 0;
}

