#include "event.h"
#include "KernelEv.h"
#include "Const.h"

Event::Event(IVTNo ivtNo){
	lock();
	myImpl=new KernelEv(ivtNo);
	unlock();
}

Event::~Event(){
	lock();
	delete myImpl;
	unlock();
	myImpl=0;
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal() {
	myImpl->signal();
}



