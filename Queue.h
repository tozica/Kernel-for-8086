/*
 * Queue.h
 *
 *  Created on: May 15, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "Thread.h"

class KernelSem;

class Queue {
public:
	friend KernelSem;
	Queue();
	PCB* u_pop();
	PCB* pu_pop();
	void decrementTime();
	void write();

	void u_push(PCB *i, unsigned);
	virtual ~Queue();
private:
	struct Elem{
		PCB* info;
		Elem* next;
		unsigned blockingTime;
		Elem(PCB *i, unsigned int t){
			info = i;
			next = 0;
			blockingTime = t;

		}
	};

	Elem *front, *rear;

};

#endif /* QUEUE_H_ */
