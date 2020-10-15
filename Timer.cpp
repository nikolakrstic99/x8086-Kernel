#include <stdio.h>
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.h"
#include "Const.h"
#include "thread.h"
#include "Special.h"
#include "KerSem.h"

extern volatile int cpuTime;
extern volatile int change;
extern volatile int m;
unsigned tsp;
unsigned tss;
unsigned tbp;

pInterrupt oldR;

void tick();


void interrupt timer(...) {
	//printf("Uso sam u promenu konteksta %d\n",m);
	m++;

	if (!change && cpuTime > 0) cpuTime--;

	//lock();
	//printf("\n-----------\n%d %d\n-----------\n",cpuTime,lockCounter);
	//unlock();

	if (change || (lockCounter==0 && cpuTime == 0 && PCB::running->timeSlice != 0)) {

		//lock();
		//printf("Uso sam u promenu konteksta %d\n",m);
		//printf("Change je:%d\n",change);
		//unlock();


#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif
		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		//lock();
		//cout<<"Pre promene"<< PCB::running->id <<"\n";
		//printf("Pre promene %d\n",PCB::running->id );
		//unlock();
		//cout<<"running->id je "<<PCB::running->id<<",  Special id je "<<PCB::special->id<<",  Status runninga je "<<PCB::running->status<<"\n";
		if(PCB::running && PCB::running!=PCB::special && PCB::running->status==2){//RUNNING==2
			PCB::running->status=READY;
			Scheduler::put((PCB*) PCB::running);
			//cout<<"stavio u sheduler " << PCB::running->id << "\n";
		}



		PCB::running = Scheduler::get();

		if (!PCB::running)			///ako ni jedna nije spreman sheduler je prazan pa uzmi special nit
		{
			PCB::running = PCB::special;
			//cout<<"Uzeo sam special nit\n";
		}
		PCB::running->status = RUNNING;
		/*
		printf("Sp je:%d\n",PCB::running->sp);
		printf("Ss je:%d\n",PCB::running->ss);
		printf("Bp je:%d\n",PCB::running->bp);
		*/
		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;
		cpuTime = PCB::running->timeSlice;

		//lock();
		//printf("Posle promene %d ",PCB::running->id);
		//printf(", novi cpuTime je %d",cpuTime);
		//printf(", change je %d",change);
		//printf(" LockCounter je %d\n",lockCounter);
		//unlock();


#ifndef BCC_BLOCK_IGNORE
			asm{
				mov sp, tsp
				mov ss, tss
				mov bp, tbp
			}
#endif



	}
	if(change==0){
#ifndef BCC_BLOCK_IGNORE
		KernelSem::tick();
		tick();
		asm int 60h;
#endif
	}
	change=0;
}

PCB* main_PCB;
void inic() {
		lock();
		cpuTime = 5;
		PCB::running = new PCB(0,5,0);
		PCB::running->status=RUNNING;


		//printf("Main PCB id je %d\n",PCB::running->id);

		Thread* s = new Special();
		PCB::special=s->myPCB;
		//printf("Special PCB id je %d\n",PCB::special->id);
		PCB::special->status=READY;

		unlock();
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	oldR = getvect(0x8);
	setvect(0x8, timer);
	setvect(0x60, oldR);
	asm sti;
#endif
}

void restore() {
	//delete main_PCB;
	//delete Thread::getThreadById(PCB::special->getId());
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(0x8, oldR);
	asm sti;
#endif
}
