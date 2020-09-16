/*
 * Thread.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "List.h"
#include "interr.h"

Thread *firstThread;
extern unsigned explicitCall;

Thread::Thread(StackSize stackSize, Time timeSlice){
	lock
		myPCB = new PCB(stackSize, timeSlice, this);
	unlock
}

void Thread::start(){
	lock
	if(myPCB->threadStatus == myPCB->NEW){
		myPCB->threadStatus == myPCB->READY;
		Scheduler::put(myPCB);
	}
	unlock
	PCB::activeThread++;
}

void Thread::waitToComplete(){
	lock

		if(!(PCB::running->threadStatus == PCB::NEW || PCB::running->myThread == this || /*PCB::running->myThread == firstThread*/ myPCB->threadStatus == PCB::TERMINATED)){
			PCB::running->threadStatus = PCB::SUSPENDED;
			this->myPCB->waittingToComplete->addElem((PCB*)PCB::running);
			dispatch();
		}

	unlock

}

ID Thread::getId(){

	return myPCB->threadID;
}

ID Thread::getRunningId(){
	if(PCB::running != 0)
		return PCB::running->threadID;
	else
		return 0;
}

Thread* Thread::getThreadById(ID id){
	PCB::allThreads.setTek();
	PCB *pom;
	int i = 0;
	while(i < id){
		pom = PCB::allThreads.getTek();
		if(pom == 0) break;
		i++;
		PCB::allThreads.movTek();
	}
	if(i == id && pom != 0)
		return pom->myThread;
	else
		return 0;

}

Thread::~Thread(){
	lock
	delete myPCB;
	unlock
}


void Thread::run(){
	cout << "AJDEEEEEEEEEEEE" << endl;
}

void dispatch(){
	lock
	explicitCall = 1;
	timer();
	unlock
}
