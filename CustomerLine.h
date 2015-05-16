/*
 * CustomerLine.h
 * PA4 - Event Simulation
 * George Karapanagos
 */

#ifndef CUSTOMERLINE_H_
#define CUSTOMERLINE_H_

#include <cstdio>
#include <cstdlib>

class CustomerLine{
public:
	class Customer;
	Customer *temp;	//temporary pointer used for traversal
	Customer *Head;	//head of the linked list
	void Insert(float aT, float tR);	//insert function
    CustomerLine();	//constructor
    ~CustomerLine();//destructor

    class Customer{
    	public:
    	Customer *Next;		//node pointing to the next node of the list
    	float arrivalTime;	//time when the customer arrives
    	float timeReq;		//time required for a customer to be served
    };

};
#endif /* CUSTOMERLINE_H_ */
