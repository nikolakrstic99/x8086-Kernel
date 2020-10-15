#include "KerSem.h"
#include "PCB.h"
#include "schedule.h"
#include "Const.h"
#include "ListaSem.h"
#include "Red.h"
#include "thread.h"

ListaSem KernelSem::allSems;

KernelSem::KernelSem(int i) {
	lock();
	allSems.push(this);
	if(i<0)i=0;
		vrednost = i;
	unlock();
}

KernelSem::~KernelSem() {
lock();
	allSems.pop(this);
	for(int i=0;i<waitOnSem.size();i++)
		deblock();
unlock();
}

int KernelSem::wait(Time maxTimeToWait) {

	--vrednost;
	if(vrednost>=0)return 1;
	else{
		int i;
		if(maxTimeToWait==0)PCB::running->waitOrNo=0;//nije vremenski ogranicena
		else PCB::running->waitOrNo=1;				//vremenski ogranicena

		lock();

		Red::Elem *elem;
		PCB::running->timeToWait=maxTimeToWait;
		elem = new Red::Elem(PCB::running);
		waitOnSem.push(elem);
		PCB::running->status=BLOCKED;

		unlock();

		dispatch();
		int time=elem->pcb->timeToWait;
		delete elem;
		if(maxTimeToWait && time==0)return 0;
		else return 1;
	}
}

int KernelSem::signal(int i) {
	if(i<0)return i;
	else if(i==0){
		if(vrednost++<0){
			deblock();
			return 0;
		}
	}else{
		//i>0
		lock();
		int j;
		for(j=0;waitOnSem.size()>0 && j<i;j++)
			deblock();

		vrednost+=i;
		unlock();
		return j;
	}
	return 0;//nikad nece
}

void KernelSem::deblock(){
	PCB* pcb=waitOnSem.getPCB();
	pcb->status=READY;
	Scheduler::put(pcb);
}

void KernelSem::tick() {

	ListaSem::Elem *cur = allSems.first;
	for(int i=0;i<allSems.n;i++){
		Red::Elem *e = cur->sem->waitOnSem.first;
					while(e) {
						if(e->pcb->timeToWait>0)e->pcb->timeToWait--;

						if(e->pcb->timeToWait==0 && e->pcb->waitOrNo==1){
			lock();
							cur->sem->waitOnSem.pop(e);
							cur->sem->vrednost++;
							e->pcb->status = READY;
							Scheduler::put(e->pcb);
			unlock();
						}
						e = e->next;
					}
					cur = cur->next;
	}
}
