/*
 * CustomerLine.cpp
 * PA4 - Event Simulation
 * George Karapanagos
 */

#include <cstdio>
#include <cstdlib>
#include "CustomerLine.h"

CustomerLine::CustomerLine() {
//initializing the Linked List
	Head=NULL;
	temp=NULL;

}

CustomerLine::~CustomerLine() {
//deleting the Linked List
	Customer *Temp = Head;
	while (Temp!=NULL) {
			Customer *q = Temp -> Next;
			delete Temp;
			Temp = q;
		}
}

void CustomerLine::Insert(float aT, float tR){
	//insert a new Node to the list;
	Customer *Temp = new Customer();
	Temp->arrivalTime=aT;
	Temp->timeReq	 =tR;
		if (!Head) {
			//if there's no head, initialize it
			Head = Temp;
		}

		else if (Temp->arrivalTime<Head->arrivalTime) {
			//if the node to be inserted has to be before the current head
			Temp -> Next = Head;
			Head = Temp;
		}

		else {
			//else check where the node is supposed to be inserted
			Customer *q = Head;
			while ((q -> Next) && (q -> Next -> arrivalTime < Temp -> arrivalTime)){
				q = q -> Next;}
			Temp -> Next = q -> Next;
			q -> Next = Temp;
		}
}

