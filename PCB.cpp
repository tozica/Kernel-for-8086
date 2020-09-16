/*
 * PCB.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include"List.h"

ID PCB::id = 0;
List PCB::allThreads;
volatile PCB* PCB::running = 0;
int PCB::activeThread = 0;
extern Thread *firstThread;

extern void dispatch();

PCB::PCB(StackSize stackSize, Time timeSlice, Thread* thread) {
lock
	sp = ss = bp = 0;
	stackSize /= sizeof(unsigned);

	timeLeft = timeSlice;

	stack = new unsigned[stackSize];

		stack[stackSize - 1] = FP_SEG(myThread);
		stack[stackSize - 2] = FP_OFF(myThread);
		stack[stackSize - 5] = 0x200;
		stack[stackSize - 6] = FP_SEG(PCB::wrapper);
		stack[stackSize - 7] = FP_OFF(PCB::wrapper);
		ss = FP_SEG(stack + stackSize - 16);
		sp = FP_OFF(stack + stackSize - 16);
		bp = sp;

		threadStatus = PCB::NEW;
		myThread = thread;

		threadID = id++;
		deblockedByTime = 0;

		waittingToComplete = new List();
		allThreads.addElem(this);
unlock
}


void PCB::wrapper(){
	PCB::running->myThread->run();

	lock
	PCB::running->threadStatus = PCB::TERMINATED;
	PCB::activeThread--;
	PCB::running->waittingToComplete->wakeAllThread();
	unlock
	dispatch();

}

PCB::~PCB(){
	lock
	delete[] stack;
	unlock
}
