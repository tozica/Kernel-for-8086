/*
 * IVTEntry.cpp
 *
 *  Created on: May 27, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include <DOS.H>
#include "KernelEv.h"

int IVTEntry::cnt = 0;
IVTEntry **IVTEntry::tableOfEntries  = new IVTEntry*[256];

IVTEntry::IVTEntry(pInterrupt newInterr, int numOfEntry) {
	if(cnt == 0){
		for(int i = 0; i < 256; i++)
			tableOfEntries[i] = 0;
		cnt++;
	}

	myEvent = 0;

	if(numOfEntry < 256 && numOfEntry >=0)
		this->numOfEntry = numOfEntry;

	oldInterr = getvect(numOfEntry);
	setvect(numOfEntry, newInterr);
	tableOfEntries[numOfEntry] = this;

}

void IVTEntry::restoreOld(){
	if(oldInterr != 0){
		setvect(numOfEntry, oldInterr);
		oldInterr = 0;
	}
}

void IVTEntry::signal(){
	if(myEvent != 0)
		myEvent->signal();
}

void IVTEntry::callOld(){
	if(oldInterr != 0)
		oldInterr();
}


IVTEntry::~IVTEntry() {
	this->restoreOld();
	tableOfEntries[numOfEntry] = 0;
}

