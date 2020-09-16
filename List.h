/*
 * List.h
 *
 *  Created on: Apr 8, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include<iostream.h>
#include"PCB.h"

class List{
	struct Elem{
		PCB *info;
		Elem *next;
		Elem(PCB *i){
			info = i;
			next = 0;
		}
	};
	int waitList;
	Elem *head, *tail, *tek;


public:
	List(){
		head = 0;
		tail = 0;
		tek = 0;
		waitList = 0;


	}
	void addElem(PCB *p){
		if(head == 0) {
			head = new Elem(p);
			tail = head;

		}
		else{
			tail->next = new Elem(p);
			tail = tail->next;
		}
	}

	void setWait(){
		waitList = 1;
	}

	void setTek(){tek = head;}
	void movTek() {tek = tek->next;}
	PCB* getTek(){return tek->info;}

	void wakeAllThread (){
		Elem *pom = head;
			while(pom != 0){
				pom->info->threadStatus = PCB::READY;
				Scheduler::put(pom->info);
				pom = pom->next;
				//cout << "Obrisao sve iz wait liste" << endl;
			}

 		}

};



#endif /* LIST_H_ */
