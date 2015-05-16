/*
 * EventQueue.cpp
 * PA4 - Event Simulation
 * George Karapanagos
 */

#include <cstdio>
#include <cstdlib>
#include "EventQueue.h"

EventQueue::EventQueue() {
//initializing the Linked List
	CurrentTime=0;
	head=NULL;
	current=NULL;
	tempo=NULL;

}

EventQueue::~EventQueue() {
//deleting the Linked List
	Event *temp = head;
	Event *q;
	while (temp!=NULL) {
			q = temp -> next;
			delete temp;
			temp = q;
		}

}

void EventQueue::Insert(float sT, float tS, int T){
	//inserting an Event to the Linked List
	Event *temp = new Event();
	temp-> startTime = sT;
	temp->timeServed = tS;
	temp-> type 	 = T;
		if (!head) {
			//if there is no head, initialize it
			head = temp;
			return;
		}

		else if (temp->startTime<head->startTime) {
			//if the event takes place before the head's event
			temp -> next = head;
			head = temp;
		}

		else {
			//else search for the proper postition to insert the event
			Event *q = head;
			while ((q -> next) && (q -> next -> startTime < temp -> startTime))
				q = q -> next;
			temp -> next = q -> next;
			q -> next = temp;
		}
}

