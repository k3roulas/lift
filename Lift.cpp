/*
 *  Lift.cpp
 *  CITI
 *
 *  Created by bob thx on 20/06/2013.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Lift.h"
#include "LiftManager.h"
#include "Man.h"

Lift::Lift(LiftManager *lift_manager, int id) : Threaded(), _id(id), _lift_manager(lift_manager) {
	this->startThread();
	cout << "creation du thread : " << _thread << endl << flush;
}
	
Lift::~Lift() {
	cout << "Destruction du Lift " << _id << endl;
}

void Lift::startThread() {
	int ret =  pthread_create(&_thread, NULL, Lift::liftLoop, this);
	if (ret != 0) {
		pthread_detach(_thread);
	}
}	
	

int Lift::start() {
	
	cout << "Start lift : " << _id << endl;
	for (; ; ) {
		// wait a new message
		pthread_mutex_lock(&_wait_mutex);				
		pthread_cond_wait (&_wait_cond, &_wait_mutex); 
		//cout << "wake up " << _id << endl << flush;
		while ( ! _level_to_process.empty() ) {
			this->nextMove();
			if ( _level_to_process.empty() ) {
				this->setStandBy();
			}
		}
		pthread_mutex_unlock(&_wait_mutex);				
		_lift_manager->retryStandByEvent();
	}
	
};

void Lift::initDirection() {
	// init direction
	if ( ! _events.empty() ) {
		Event *e = _events.front();
		if (e->getStart() == this->getPosition()) {
			e->isEventUp() ? this->setUp() : this->setDown();				
		} else {
			(this->getPosition() < e->getStart()) ? this->setUp() : this->setDown(); 
		}
	}	
}	

void Lift::nextMove() {
	
	if (this->isStandBy() ) {
		this->initDirection();
	}
	
	if ( ! this->isStandBy() ) {
		
		// move to next level
		if (this->isUp()) {
			_position++;
		} else {
			_position--;
		}
		
		cout << "LIFT " << _id << " Move - level : " << _position << endl;
		sleep(2);
		
		
		// it has to stop ?
		set<int>::iterator it;
		it=_level_to_process.find(_position);
		if (it != _level_to_process.end()) {
						
			// yes
			_level_to_process.erase (it);
			
			this->deliver();
			
			// check if routing match
			if ( this->getRoutingLevel() == this->getPosition() ) {
				this->setStandBy();
			}
			
			this->boardIn();

			
			
			
		}
	}
	
}
void Lift::boardIn() {
	for(int i=0; i<_events.size(); i++ ) {								
		Event *e = _events[i];
		if ( e->getStart() == _position ) {
			e->setInProcess();
			const Man& m= e->getMan();
			cout << "LIFT " << _id << " Board in " << m.getName() << " to " << e->getEnd() << endl;
			_level_to_process.insert( e->getEnd() );
		}
	}	
}


void Lift::deliver() {
	// remove _event for this level
	vector<Event*>::iterator ite;
	ite = _events.begin();
	for( ; ite != _events.end();)
	{
		Event *e = *ite;
		if ( e->getEnd() == _position ) {
			ite = _events.erase(ite);
			const Man& m= e->getMan();
			cout << "LIFT " << _id << " Deliver " << m.getName()  << endl;
			delete e;
		}
		else
			++ite;
	}
}
	
void * Lift::liftLoop(void *data) {
		Lift *l = (Lift *) data;
		l->start();
	}
	
	
	void Lift::addRoutingEvent(Event *e) {
		this->setRouting();
		this->setRoutingLevel(e->getStart());
		_events.push_back(e);
		_level_to_process.insert(e->getStart());
		this->refreshChecker();
	}
	
	
	void Lift::addEvent(Event *e) {
		_events.push_back(e);
		_level_to_process.insert(e->getStart());
		this->refreshChecker();
	}
	
	void Lift::refreshChecker() {
		pthread_mutex_lock (&_wait_mutex);		/* On verrouille le mutex */
		pthread_cond_signal (&_wait_cond);		/* On d√©livre le signal : condition remplie */
		pthread_mutex_unlock (&_wait_mutex);	/* On d√©verrouille le mutex */		
	}
	
	void Lift::Print() {
		cout << "Print Lift " << _id << endl;
	}
	
	void Lift::setRouting() { _state = 0; }
	void Lift::setDelivering() { _state = 0; }
	int Lift::isRouting() { return _state == 0; }
	int Lift::getPosition() { return _position; }
	void Lift::setStandBy() {  _direction = 0; }
	int Lift::isStandBy() { return _direction ==0; }	
	int Lift::isUp() { return _direction ==1; }	
	int Lift::isDown() { return _direction ==2; }	
	void Lift::setUp() { _direction =1; }	
	void Lift::setDown() { _direction =2; }	
	void Lift::setRoutingLevel(int level) { _routing_level = level; }	
	int Lift::getRoutingLevel() { return _routing_level; }	
