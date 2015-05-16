/*
 * qSim.cpp
 * PA4 - Event Simulation
 * George Karapanagos
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <time.h>

#include "EventQueue.h"
#include "CustomerLine.h"




float  RaT;	//Random arrival Time
float  RtR;	//Random time Required
float  tI;	//time Idle


int main(int argc, char *argv[]) {

	srand(time(NULL)); //the seed of rand
	EventQueue E;	//EventQueue for the COMMON LINE SIMULATION
	CustomerLine C;	//CustomerLine for the COMMON LINE SIMULATION
	//initializing all the variables used for statistics

	int CustomersServed	=0;
	float TimeWaiting	=0;
	float MaxTime		=0;
	float TotalSTime	=0;
	float TotalITime	=0;
	//initializing the constants of the simulation
	const int Customers = atof(argv[1]);
	const int Tellers   = atof(argv[2]);
	const float SimulationTime = atof(argv[3]);
	const float AverageTime    = atof(argv[4]);
	const int TellerFree 		= 1;
	const int CustomerArrival 	= 2;
	const int CustomerComplete 	= 3;
	for (int i = 0; i < Customers; i++)
	{
		//initialize the Customers in the Common Customer Line
		RaT = SimulationTime*rand()/float(RAND_MAX);
		RtR = 2*AverageTime*rand()/float(RAND_MAX);
		C.Insert(RaT, RtR);
	}

	for (int i = 0; i< Tellers; i++){
		//initialize the tellers as free at time=0
		E.Insert(E.CurrentTime, 0, TellerFree);
	}

	C.temp=C.Head;
	while(C.temp){
		//adding the customer arrival events, to the event queue
		E.Insert(C.temp->arrivalTime, C.temp->timeReq, CustomerArrival);
		C.temp=C.temp->Next;
	}

	E.current = E.head;
	bool check;
	while(	(CustomersServed<Customers)	&&	((E.CurrentTime) < SimulationTime)	){
		E.tempo = E.head;
		check=false;

		if(E.current->type==TellerFree ){
			//ACTION OF A TELLER
			while((E.tempo)&&(check==false))
			{	//check to find a teller free event type-1
				if((E.tempo->type==CustomerArrival)&&(E.tempo->startTime<E.current->startTime))
				{	//check to find a customer already in the common line type-2
					E.Insert((E.current->startTime+E.tempo->timeServed), 0, CustomerComplete);
					E.Insert((E.current->startTime+E.tempo->timeServed), 0, TellerFree );
					E.tempo->type=CustomerComplete;
					//make the customer event to a customer complete event
					check=true;
					//check that the teller actually worked (so no reason to idle him)
					CustomersServed++;
					//increment the numbers of customers served
					TimeWaiting=TimeWaiting+(E.current->startTime-E.tempo->startTime)+E.tempo->timeServed;
					//increase the time waiting of a customer by the difference of the
					//time he got served and the time he arrived at the bank

					if((E.current->startTime-E.tempo->startTime)>MaxTime){
						//if the waiting time is bigger than the max waiting time
						//set the new to max to the current difference
						MaxTime=(E.current->startTime-E.tempo->startTime);
					}

					TotalSTime=TotalSTime+E.tempo->timeServed;
					//increase the total amount of service
				}

				E.tempo=E.tempo->next;
				//go to the next event
			}
			if(check==false){
								//if no customer found, set teller to idle
								tI= 1.5*rand()/float(RAND_MAX);
								E.Insert((E.current->startTime+tI), 0, TellerFree );
								TotalITime=TotalITime+tI;
							}
			E.current->type=0; //the tellerFree is no longer at this event so make the type NULL
					}

		E.current=E.current->next;
		E.CurrentTime=E.current->startTime;
	}	//END BIG WHILE-LOOP

	TimeWaiting=TimeWaiting/CustomersServed;
	//get the average waiting time


	//print the output to a file
	std::ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << "     This is the output for a Common Line!    \n";
	outputFile << "----------------------------------------------" << std::endl;
	outputFile << "Number of customers served: " << CustomersServed << std::endl;
	outputFile << "Total time to serve them all: " << E.CurrentTime << std::endl;
	outputFile << "Number of tellers: " << Tellers << std::endl;
	outputFile << "Average time a customer spent in the bank: " << TimeWaiting << std::endl;
	outputFile << "Max waiting time of a customer: " << MaxTime << CustomersServed << std::endl;
	outputFile << "Total amount of teller service: " << TotalSTime << CustomersServed << std::endl;
	outputFile << "Total amount of tellers being idle: " << TotalITime << CustomersServed << std::endl;
	outputFile.close();



	//END OF SIMULATION ONE, COMMON LINE
	//START SIMULATION FOR SEPERATE LINES
	//re-initialize all statistic variables
	srand(time(NULL));
	CustomersServed	=0;
	TimeWaiting		=0;
	MaxTime			=0;
	TotalSTime		=0;
	TotalITime		=0;
	CustomerLine F[Tellers];	//create an array of lists for the separate customer lines
	EventQueue   D;				//Event Queue for the separate lines simulation

	//initiate one customer line for each teller
	for (int i = 0; i < Customers; i++)
		{
			//initialize the Customers in the Common Customer Line
			RaT = SimulationTime*rand()/float(RAND_MAX);
			RtR = 2*AverageTime*rand()/float(RAND_MAX);
			F[(i%(Tellers))].Insert(RaT, RtR);
		}
	//add in the event queue all the tellers
	for (int i = 0; i< Tellers; i++){
			//initialize the tellers as free at time=0
			D.Insert(D.CurrentTime, 0, i);
		}

	//add in the event queue all the customer lines
	for(int i = 0; i < Tellers; i++){
		F[i].temp=F[i].Head;
		while(F[i].temp){
			D.Insert(F[i].temp->arrivalTime, F[i].temp->timeReq, i+Tellers);
			F[i].temp=F[i].temp->Next;
		}
	}

	D.current = D.head;
		while(	(CustomersServed<Customers)	&&	((D.CurrentTime) < SimulationTime)	){
			D.tempo = D.head;
			check=false;

			if(D.current->type<Tellers){
				//scan the event queue for the first teller
				while((D.tempo)&&(check==false))
				{	//ACTION OF A TELLER
					//check if he has any customer in his line
					if((D.tempo->type==((D.current->type)+Tellers))&&(D.tempo->startTime<D.current->startTime))
					{
					//if yes, serve him
						D.Insert((D.current->startTime+D.tempo->timeServed), 0, 2*Tellers+1);
						D.Insert((D.current->startTime+D.tempo->timeServed), 0, D.current->type);
						D.tempo->type=2*Tellers+1;
						D.current->type=2*Tellers+1;
						check=true;
						CustomersServed++;
						//increment the customers served variable
						TimeWaiting=TimeWaiting+(D.current->startTime-D.tempo->startTime)+D.tempo->timeServed;
						if((D.current->startTime-D.tempo->startTime)>MaxTime){
							MaxTime=(D.current->startTime-D.tempo->startTime);
						}

						TotalSTime=TotalSTime+D.tempo->timeServed;
						//add to the total amount of service time
					}

					D.tempo=D.tempo->next;
				}
				//if not, check the other lines
				D.tempo = D.head;
				while((D.tempo)&&(check==false)){
				if(((D.tempo->type)>Tellers)&&((D.tempo->type)<2*Tellers+1)&&(D.tempo->startTime<D.current->startTime))
									{
					//if yes, serve him
					D.Insert((D.current->startTime+D.tempo->timeServed), 0, 2*Tellers+1);
					D.Insert((D.current->startTime+D.tempo->timeServed), 0, D.current->type);
					D.tempo->type=2*Tellers+1;
					D.current->type=2*Tellers+1;
					check=true;
					CustomersServed++;
					//increment the number of customers served
					TimeWaiting=TimeWaiting+(D.current->startTime-D.tempo->startTime)+D.tempo->timeServed;
					//add to the waiting time the difference between the arrival
					//time of the customer and when he got served
				if((D.current->startTime-D.tempo->startTime)>MaxTime){
					//if the difference is the biggest observed
					//make the max waiting time to the current one
					MaxTime=(D.current->startTime-D.tempo->startTime);}

				TotalSTime=TotalSTime+D.tempo->timeServed;
				//add to the total service time
									}
				D.tempo=D.tempo->next;
			}
				if(check==false){
					//if no customers found idle him
									tI= 1.5*rand()/float(RAND_MAX);
									D.Insert((D.current->startTime+tI), 0, D.current->type);
									TotalITime=TotalITime+tI;
								}
				D.current->type=2*Tellers+1;
				//the teller of this event already did his job and got moved to another
				//event in the queue, so the type of this node is set to something big
						}

			D.current=D.current->next;
			D.CurrentTime=D.current->startTime;
		}	//END BIG WHILE-LOOP

		TimeWaiting=TimeWaiting/CustomersServed;
		//get the average waiting time

		//print the output to a file
		std::ofstream outputFile2;
		outputFile.open("output2.txt");
		outputFile << "     This is the output for the Separate Lines!    \n";
		outputFile << "----------------------------------------------" << std::endl;
		outputFile << "Number of customers served: " << CustomersServed << std::endl;
		outputFile << "Total time to serve them all: " << D.CurrentTime << std::endl;
		outputFile << "Number of tellers: " << Tellers << std::endl;
		outputFile << "Average time a customer spent in the bank: " << TimeWaiting << std::endl;
		outputFile << "Max waiting time of a customer: " << MaxTime << CustomersServed << std::endl;
		outputFile << "Total amount of teller service: " << TotalSTime << CustomersServed << std::endl;
		outputFile << "Total amount of tellers being idle: " << TotalITime << CustomersServed << std::endl;
		outputFile.close();

	//E.~EventQueue();			// delete the event queue linked list
	//C.~CustomerLine();		// delete the customer line linked list
	//D.~EventQueue();			// delete the event queue linked list
	for (int i = 0; i< Tellers; i++){
	//	F[i].~CustomerLine();	// delete the customer line linked list
	}
	return EXIT_SUCCESS;
}


