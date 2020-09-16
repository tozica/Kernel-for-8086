/*
 * Thread.h
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

#include "macros.h"

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;
class PCB; // Kernel's implementation of a user's thread



class Thread {
public:
 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
protected:
 friend class PCB;
 friend void inic();
 friend void restore();
 friend void interrupt timer(...);
 virtual void run();
private:
 PCB* myPCB;
};
void dispatch ();


#endif /* THREAD_H_ */
