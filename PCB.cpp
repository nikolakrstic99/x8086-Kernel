#include <stdio.h>
#include <dos.h>
#include "PCB.h"
#include "Const.h"
#include "SCHEDULE.h"

int PCB::nextId = 1;
List<PCB*> PCB::allPCBs;
PCB* PCB::running = 0;
PCB* PCB::special = 0;


void PCB::wrapper(){
	//cout<<"Id trenutne niti je "<<running->id<<"\n";
	//printf("Id trenutne niti je %d\n",running->id);
	PCB::running->myThread->run();

	lock();
	running->status=TERMINATED;

	for(int i=0;i<running->waitingForMe.size();i++){	//notify all
		lock();
		PCB* tmp=running->waitingForMe.getPCB();
		tmp->status=READY;
		Scheduler::put(tmp);
		unlock();
	}



	unlock();
	dispatch();
};

PCB::PCB(StackSize size, Time time, Thread *t){

	myThread=t;
	status=NEW;
	timeSlice=time;
	stack=0;
	timeToWait=waitOrNo=0;

	if (size<minStackSize) size = minStackSize;
	if (size>maxStackSize) size = maxStackSize;

	lock();
	size /= sizeof(unsigned);
	stack=new unsigned[size];
	id=nextId++;
	unlock();

	stack[size-1]=0x200;
	bp=sp=ss=0;
	#ifndef BCC_BLOCK_IGNORE
		stack[size-2]=FP_SEG(PCB::wrapper);
		stack[size-3]=FP_OFF(PCB::wrapper);
		bp = FP_OFF(stack + size - 12);
		sp = bp;
		ss = FP_SEG(stack + size - 12);
	#endif


	//allPCBs.add(this);
	allPCBs.push(this);
};

PCB::~PCB(){
	waitToComplete();
	//PCB::allPCBs.remove(this->getId());

	PCB::allPCBs.remove(this);

	if (stack != 0) {
		delete stack;
	}
	stack = 0;
};

void PCB::start(){
	lock();
	if(this != PCB::special && this->status == 0) {//NEW==0

			this->status = READY;
			Scheduler::put(this);
			//cout<<"ubacena u SCHEDULER " << id << "\n";
	}
	unlock();

};

void PCB::waitToComplete(){

	if(PCB::running!=this && this!=PCB::special && this->status!=0 && this->status!=4 ){ //TERMINATED==4
		lock();
		running->status=BLOCKED;

		//printf("%d waiting for %d\n",PCB::running->id,id);
		//cout<< running->id <<" waiting for "<< id <<"\n";
		waitingForMe.push(running);

		unlock();
		dispatch();

	}

};


