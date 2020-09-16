/*
 * KernelEv.cpp
 *
 *  Created on: May 27, 2020
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTEntry.h"
#include "PCB.h"

KernelEv::KernelEv(IVTNo ivtNo) {
	IVTEntry::tableOfEntries[(int)ivtNo]->myEvent = this;
	myPCB = (PCB*)PCB::running;
	value = 1;
}


void KernelEv::wait(){
	if(value - 1 < 0)
		return;

	if(--value == 0 && myPCB == PCB::running){
		if(myPCB != 0)
			myPCB->threadStatus = PCB::SUSPENDED;
		dispatch();
	}

}

void KernelEv::signal(){
	if(value + 1 > 1)
		return;

	if(++value == 1){
		myPCB->threadStatus = PCB::READY;
		Scheduler::put(myPCB);
		value++;
	}
}




KernelEv::~KernelEv() {
	// TODO Auto-generated destructor stub
}

