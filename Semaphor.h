/*
 * Semaphor.h
 *
 *  Created on: Jul 5, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "macros.h"

typedef unsigned int Time;
class KernelSem;


class Semaphore {
public:
	Semaphore (int init=1);
	virtual ~Semaphore ();
	virtual int wait (Time maxTimeToWait);
	virtual int signal(int n=0);
	int val () const; // Returns the current value of the semaphore
private:
	KernelSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
