/*
 * interr.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#include "interr.h"
#include "PCB.h"
#include <IOSTREAM.H>
#include "KernSem.h"

unsigned oldTimerSEG = 0, oldTimerOFF = 0;
volatile int cnt = 2;
volatile int explicitCall = 0;
unsigned tsp = 0, tss = 0, tbp = 0;
extern Thread* firstThread;
volatile Thread *tmpThread = 0;
EmptySchedule* EmptySchedule::Empty = 0;
void tick();


void interrupt timer(...){
	if(!explicitCall)
		KernelSem::notifyAll();
	if(!explicitCall && cnt != infinity){
			cnt--;
			//KernelSem::notifyAll();
		}
		if(explicitCall || cnt == 0){
			asm{
					mov tsp, sp
					mov tss, ss
					mov tbp, bp
				}

				PCB::running->sp = tsp;
				PCB::running->ss = tss;
				PCB::running->bp = tbp;

				if(PCB::running->threadStatus == PCB::RUNNING){
					PCB::running->threadStatus = PCB::running->READY;
					Scheduler::put((PCB*)PCB::running);
				}

				//cout << "ID pre promene " << PCB::running->myThread->getId() << endl;
			//	asm cli

				PCB::running = Scheduler::get();
				if(PCB::running == 0){
					PCB::running = EmptySchedule::Empty->myPCB;
					PCB::running->threadStatus = PCB::NEW;
				}
				PCB::running->threadStatus = PCB::RUNNING;

				//cout << "ID posle promene " << PCB::running->myThread->getId()<< endl;
				//asm cli

				cnt = PCB::running->timeLeft;

				tsp = PCB::running->sp;
				tss = PCB::running->ss;
				tbp = PCB::running->bp;

				asm{
					mov ss, tss
					mov sp, tsp
					mov bp, tbp
				}
		}
		if(!explicitCall) {
			tick();
			asm int 60h;
		}
		explicitCall = 0;
}

void inic(){

	asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax // es = 0

			// pamti staru rutinu
			mov ax, word ptr es:0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			// postavlja novu rutinu
			mov word ptr es:0022h, seg timer
			mov word ptr es:0020h, offset timer

			// postavlja staru rutinu
	        // na int 60h - zasto?
			mov ax, oldTimerSEG
			mov word ptr es:0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
	firstThread = new Thread();
	PCB::running = firstThread->myPCB;
	PCB::running->threadStatus = PCB::running->RUNNING;
	EmptySchedule::Empty = new EmptySchedule(4096,1);
}


void restore(){
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}

}
