/*
 * KernSem.h
 *
 *  Created on: Jul 5, 2020
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

class Queue;

class KernelSem {
public:
	struct AllSems{
			KernelSem *info;
			AllSems *next;
			AllSems(KernelSem *node){
				info = node;
				next = 0;
			}
		};

	KernelSem(int init);

	int signal(int);
	int wait(int);
	int getVal();
	static void notifyAll();
	virtual ~KernelSem();
private:
	int val;
	Queue *queue;
	static AllSems *head, *tail;
	void unblockOneSem();
};

#endif /* KERNSEM_H_ */
