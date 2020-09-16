/*
 * KernSem.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: OS1
 */

#include "KernSem.h"
#include "Queue.h"
#include "PCB.h"
#include <IOSTREAM.H>

KernelSem::AllSems *KernelSem::head = 0;
KernelSem::AllSems *KernelSem::tail = 0;

KernelSem::KernelSem(int init) {
	val = init;
	queue = new Queue();
	if(head == 0){
		head = new AllSems(this);
		tail = head;
	}
	else{
		tail->next = new AllSems(this);
		tail = tail->next;
	}

}

int KernelSem::wait(int MaxTimeToWait){
	if(--val < 0){
		queue->u_push((PCB*)PCB::running, MaxTimeToWait);
		PCB::running->threadStatus = PCB::SUSPENDED;
		dispatch();
	}
	if(PCB::running->deblockedByTime == 1){
		PCB::running->deblockedByTime = 0;
		return 0;
	}
	else{
		PCB::running->deblockedByTime = 0;
		return 1;
	}
}

void KernelSem::unblockOneSem(){
	PCB* tmp = queue->u_pop();
	tmp->threadStatus = PCB::READY;
	Scheduler::put(tmp);
}

int KernelSem::signal(int n){
	if(n > 0){
		int i = 0;
		for(i = 0; i < n && val < 0; i++){
			if(val++ < 0){
				this->unblockOneSem();
			}
		}
		return i;
	}
	if(val++ < 0){
		this->unblockOneSem();
	}
	return 0;

}


/*void KernelSem::notifyAll(){
	AllSems *allSemsTmp = KernelSem::head;
	while(allSemsTmp != 0){
		Queue *tmpQueue = allSemsTmp->info->queue;
		Queue::Elem *tmpElem = tmpQueue->front;
		while(tmpElem != 0){
			cout << tmpElem->blockingTime << endl;
			if(tmpElem->blockingTime == infinity)
				continue;

			if(--tmpElem->blockingTime == 0){
				allSemsTmp->info->val++;
				PCB* tmp = tmpQueue->pu_pop();
				tmp->threadStatus = PCB::READY;
				Scheduler::put(tmp);
				tmp->deblockedByTime = 1;
				tmpElem = tmpQueue->front;
			}
			else
				tmpElem = tmpElem->next;
		}
		allSemsTmp = allSemsTmp->next;
	}
}*/


void KernelSem::notifyAll(){
	AllSems *allSemsTmp = head;
	while(allSemsTmp != 0){
		Queue *pqueue = allSemsTmp->info->queue;
		Queue::Elem *element = pqueue->front;
		while(element != 0){
		//	cout << element->blockingTime << endl;
			//asm cli;
			if(element->blockingTime != infinity){
				if(--element->blockingTime == 0){
					allSemsTmp->info->val++;
					PCB* unblock = pqueue->pu_pop();
					unblock->threadStatus = unblock->READY;
					unblock->deblockedByTime = 1;
					Scheduler::put(unblock);
					element = pqueue->front;
				}
				else
					element = element->next;
			}
			else
				element = element->next;

		}


		allSemsTmp = allSemsTmp->next;

	}
}

int KernelSem::getVal(){
	return val;
}

KernelSem::~KernelSem() {
	// TODO Auto-generated destructor stub
}

