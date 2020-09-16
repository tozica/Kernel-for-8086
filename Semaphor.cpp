/*
 * Semaphor.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KernSem.h"

Semaphore::Semaphore(int init){
	lock
	myImpl = new KernelSem(init);
	unlock
}

int Semaphore::wait(Time maxTimeToWait){
	lock
	if(maxTimeToWait == 0)
		maxTimeToWait = infinity;
	int ret = myImpl->wait(maxTimeToWait);
	unlock
	return ret;
}

int Semaphore::signal(int n){
	lock
	int ret = myImpl->signal(n);
	unlock
	return ret;
}

int Semaphore::val()const{
	return myImpl->getVal();
}

Semaphore::~Semaphore(){
	lock
	delete myImpl;
	unlock
}
