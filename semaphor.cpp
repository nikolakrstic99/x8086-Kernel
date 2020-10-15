#include "KerSem.h"
#include "semaphor.h"

Semaphore::Semaphore(int init){
	myImpl=new KernelSem(init);
};

int Semaphore::val()const{
	return myImpl->val();
};

int Semaphore::signal(int n){
	return myImpl->signal(n);
};

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
};

Semaphore::~Semaphore(){
	delete myImpl;
};





