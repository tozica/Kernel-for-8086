/*
 * KernelEv.h
 *
 *  Created on: May 27, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "macros.h"

class PCB;

class KernelEv {
public:
	KernelEv(IVTNo ivtNo);

	void wait();
	void signal();

	PCB *myPCB;
	volatile int value;

	IVTNo ivtNo;

	virtual ~KernelEv();
};

#endif /* KERNELEV_H_ */
