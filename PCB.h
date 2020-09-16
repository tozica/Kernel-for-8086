/*
 * PCB.h
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
#include "macros.h"

class List;

class PCB {
public:
	PCB(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice, Thread*);
	void waitToComplete();
	friend class Thread;

	enum Status{NEW, READY, RUNNING, SUSPENDED, TERMINATED};
	Status threadStatus;
	int deblockedByTime;
	List *waittingToComplete;

	unsigned *stack;
	unsigned ss, sp, bp;
	Time timeLeft;
	ID threadID;

	Thread* myThread;
	static List allThreads;
	static volatile PCB* running;
	static void wrapper();
	static int activeThread;



	virtual ~PCB();
private:
	static ID id;
};

#endif /* PCB_H_ */
