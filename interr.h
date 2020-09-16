/*
 * interr.h
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#ifndef INTERR_H_
#define INTERR_H_
#include "Thread.h"
#include "IOSTREAM.H"
void interrupt timer(...);
void inic();
void restore();

class EmptySchedule: public Thread{
public:
	EmptySchedule(unsigned int i, unsigned j):Thread(i, 1){}
	virtual void run(){
		for(;;);


	}
	friend void interrupt timer(...);
	friend void inic();
private:
	static EmptySchedule *Empty;
};

#endif /* INTERR_H_ */
