#include "PCB.h"
#include "thread.h"
#include "List.h"
#include "Const.h"

//void interrupt timer(...);

extern volatile int change;

void dispatch(){
	change=1;
	asm int 8h;							//////// 0x8?  8h?
}

Thread::Thread(StackSize size,Time time){
	lock();
	myPCB=new PCB(size,time,this);
	unlock();
}

Thread::~Thread(){
	delete myPCB;
	myPCB=0;
}

void Thread::start() {
	if (myPCB==0) return;
	myPCB->start();
}

void Thread::waitToComplete() {
	if (myPCB==0) return;
	myPCB->waitToComplete();
}

ID Thread::getId() {
	if (myPCB==0) return -1;
	return myPCB->getId();
}

ID Thread::getRunningId() {
	return PCB::running->getId();
};


Thread* Thread::getThreadById(ID id) {
	return PCB::getThreadById(id);
}
