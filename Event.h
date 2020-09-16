/*
 * Event.h
 *
 *  Created on: May 27, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include"macros.h"
#include "IVTEntry.h"


class KernelEv;

#define PREPAREENTRY(IVTNo,old)\
void interrupt intr##IVTNo(...);\
IVTEntry entry##IVTNo(intr##IVTNo,IVTNo);\
void interrupt intr##IVTNo(...) {\
	if (old) entry##IVTNo.callOld();\
	entry##IVTNo.signal();\
}

class Event {
public:

 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();

protected:

 friend class KernelEv;
 void signal(); // can call KernelEv

private:
 KernelEv* myImpl;
};


#endif /* EVENT_H_ */
