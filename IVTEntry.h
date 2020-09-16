/*
 * IVTEntry.h
 *
 *  Created on: May 27, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "macros.h"

class KernelEv;

class IVTEntry {
public:
	IVTEntry(pInterrupt, int numOfEntry);
	static IVTEntry **tableOfEntries;


	int numOfEntry;
	pInterrupt oldInterr;
	KernelEv *myEvent;

	void restoreOld();
	void callOld();
	void signal();

	virtual ~IVTEntry();
private:
	static int cnt;
};

#endif /* IVTENTRY_H_ */
