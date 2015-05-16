/*
 * EventQueue.h
 * PA4 - Event Simulation
 * George Karapanagos
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <cstdio>
#include <cstdlib>

class EventQueue{
public:
	EventQueue();	//constructor
	~EventQueue();	//destructor
	class Event;	//class of the linked list's nodes
	float CurrentTime;
	void Insert(float sT, float tS, int T);
	Event *head;	//head of the list
	Event *current; //temporary nodes used for
	Event *tempo;	//traversal of the list
	class Event{
		public:
		float startTime, timeServed;	//starting time of the event and time reuired for it to be served
		Event* next; //node pointing to the next event of the queue
		int type;	 //enumeration to distinguish between types of events
	};

};



#endif /* EVENTQUEUE_H_ */
