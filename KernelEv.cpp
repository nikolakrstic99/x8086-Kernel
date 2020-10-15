#include "KernelEv.h"
#include "PCB.h"
#include "schedule.h"
#include "Const.h"
#include "thread.h"

KernelEv* KernelEv::arrayOfEvents[256] = {0};

KernelEv::KernelEv(IVTNo ivtno):sem(0),ivt(ivtno),blokiran(0) {
	vlasnik = PCB::running;
	KernelEv::arrayOfEvents[ivt] = this;
}

KernelEv::~KernelEv() {
	KernelEv::arrayOfEvents[ivt] = 0;
	if(blokiran != 0) {
		deblock();
		vlasnik = 0;
	}
}

void KernelEv::wait() {
	if(PCB::running == vlasnik) {
		if(sem == 0) block();
		sem = 0;
	}
}

void KernelEv::signal() {
	if(blokiran!=0)
		deblock();
	else sem=1;
}

void KernelEv::block(){
	lock();
	blokiran = vlasnik;
	blokiran->status = BLOCKED;
	unlock();
	dispatch();
}

void KernelEv::deblock(){
	lock();
	blokiran->status = READY;
	Scheduler::put(blokiran);
	blokiran = 0;
	unlock();
}
