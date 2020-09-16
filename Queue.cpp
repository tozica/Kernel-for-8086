/*
 * Queue.cpp
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#include "Queue.h"
#include <IOSTREAM.H>

Queue::Queue() {
	front = 0;
	rear = 0;


}

PCB* Queue::u_pop(){
	lock
	if(front == 0){
		unlock
		return 0;
	}
	else{
		Elem *pom = front;
		front = front->next;
		if(front == 0)
			rear = 0;
		PCB* back = pom->info;
		unlock
		delete pom;
		return back;
	}
}

void Queue::u_push(PCB *i, unsigned t){
	lock
	if(t == 0){
		t = infinity;
		unlock
	}
		if(front == 0){
		front = new Elem(i, t);
		rear = front;
		unlock
	}
	else{
		rear->next = new Elem(i, t);
		rear = rear->next;
		unlock
	}
}

PCB* Queue::pu_pop(){
	lock
	Elem *pom = front;
	Elem *pret = 0;
	while(pom != 0){
		if(pom->blockingTime == 0){
			if(pret == 0){
				Elem *pom1 = front;
				front = front->next;
				PCB* back = pom1->info;
				delete pom1;
				unlock
				return back;
			}
			else{
				Elem *pom1 = pom;
				pret->next = pom1->next;
				PCB* back = pom1->info;
				if(front == 0)
					rear = 0;
				if(pom == front)
					front == pret;
				delete pom1;
				unlock
				return back;
			}
		}
		pret = pom;
		pom = pom->next;
	}
	unlock
	return 0;
}

void Queue::decrementTime(){
	Elem* pom = front;
	while(pom != 0){
		if(pom->blockingTime != infinity){
			pom->blockingTime--;
		}

		pom = pom->next;
	}
}

/*void Queue::write(){
	Elem *pom = front;
	while(pom){
		cout << pom->blockingTime << endl;
		pom = pom->next;

	}
}*/

Queue::~Queue() {
	// TODO Auto-generated destructor stub
}

