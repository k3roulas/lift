/*
 *  LiftManager.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "LiftManager.h"

LiftManager::LiftManager(int nb_levels, int nb_lifts) : Threaded(), _nb_levels(nb_levels), _nb_lifts(nb_lifts)
	{
		
		this->startThread();
		cout << "Create thread manager : " << _thread << endl << flush;
		
		_lifts = vector<Lift*>(nb_lifts);
		for (int i=0; i< _nb_lifts; i++) {
			Lift *l = new Lift(this,i);
			_lifts[i]=l;
		}		
	}

LiftManager::~LiftManager()
{
	
	for (int i=0; i< _nb_lifts; i++) {
		delete _lifts[i];
	}		
}

void LiftManager::startThread() {
	int ret =  pthread_create(&_thread, NULL, LiftManager::liftManagerLoop, this);
	if (ret != 0) {
		pthread_detach(_thread);
	}
}
	
	void LiftManager::addEvent(const Man &m, int start, int end) {
		Event *e = new Event(m, start, end);
		_events_new.push_back(e);
		this->refreshChecker();
	}
	
	
	void LiftManager::retryStandByEvent() {
		this->refreshChecker();
	}
	
	void LiftManager::refreshChecker() {
		pthread_mutex_lock (&_wait_mutex);		/* On verrouille le mutex */
		pthread_cond_signal (&_wait_cond);		/* On délivre le signal : condition remplie */
		pthread_mutex_unlock (&_wait_mutex);	/* On déverrouille le mutex */		
	}
	
	
	int LiftManager::start() {		
		
		cout << "demarrage lift manager." << endl;
		for (; ; ) {
			// wait a new message from main, or from lifts
			pthread_mutex_lock(&_wait_mutex);				/* On verrouille le mutex */
			pthread_cond_wait (&_wait_cond, &_wait_mutex);  /* On attend que la condition soit remplie */		
			cout << "wake up lift manager" << endl << flush;
			
			// tant que la liste n'est pas vide on traite
			deque<Event *>::iterator it = _events_new.begin();
			while (it != _events_new.end()) {
				Event *e = *it;
				this->processNewEvent(e);
			}
			it = _events_stand_by.begin();
			while (it != _events_stand_by.end()) {
				Event *e = *it;
				if (this->processEvent(e)) {
					it = _events_stand_by.erase(it);
				} else {
					++it;
				}
			}			
			pthread_mutex_unlock(&_wait_mutex);				/* On déverrouille le mutex */
		}
	};
	
	void * LiftManager::liftManagerLoop(void *data) {
		LiftManager *l = (LiftManager *) data;
		l->start();
	}	
		
	
	int LiftManager::processEvent(Event *e) {
		
		Lift *l;
		
		// check if there is a lift in stand by
		//  -> yes choose the closer
		int closer_lift = -1;
		int distance = _nb_levels + 1;
		
		for (int i=0; i<_nb_lifts; i++) {
			l = _lifts[i];
			
			if (l->isStandBy()) {
				
				if (abs(e->getStart() - l->getPosition()) < distance) {
					closer_lift = i;	
				}
				
			}
			
		}
		
		if (closer_lift != -1) {
			l = _lifts[closer_lift];
			l->addRoutingEvent(e);
			return 1;
		}
		
		// check the list of lift that are in the way of this event
		//  -> yes assign event to this lift
		closer_lift = -1;
		distance = _nb_levels + 1;
		for (int i=0; i<_nb_lifts; i++) {
			l = _lifts[i];
			if (e->isEventUp()) {
				if (l->isUp() && l->getPosition() < e->getStart()) {
					if (l->isRouting()) {
						if (l->getRoutingLevel() >= e->getEnd() ) {
							if (abs(e->getStart() - l->getPosition()) < distance) {
								closer_lift = i;	
							}
						}
					} else {
						if (abs(e->getStart() - l->getPosition()) < distance) {
							closer_lift = i;	
						}
					}
				}
				
			} else { // event is down
				if (l->isDown() && l->getPosition() > e->getStart()) {
					if (l->isRouting()) {
						if (l->getRoutingLevel() >= e->getEnd() ) {
							if (abs(e->getStart() - l->getPosition()) < distance) {
								closer_lift = i;	
							}
						}
					} else {
						if (abs(e->getStart() - l->getPosition()) < distance) {
							closer_lift = i;	
						}
					}
				}				
			}
			
		}
		
		if (closer_lift != -1) {
			l = _lifts[closer_lift];
			l->addEvent(e);
			return 1;
		}
		
		return 0;
		
		
	}
	
	void LiftManager::processNewEvent(Event *e) {
		
		if ( !this->processEvent(e) ) {	
			_events_stand_by.push_back(e);
		}
		
	}
	
	void LiftManager::processNewEvent(const Man &m, int start, int end) {
		
		Event *e = new Event(m, start, end);
		if ( !this->processEvent(e) ) {	
			_events_stand_by.push_back(e);
		}
		
	}
	