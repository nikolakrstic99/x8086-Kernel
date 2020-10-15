#ifndef _kernel_sem_h_
#define _kernel_sem_h_
#include "Const.h"
#include "ListaSem.h"
#include "Red.h"

class KernelSem {
public:
	KernelSem(int init);
	~KernelSem();

	int wait(Time maxTimeToWait);
	int signal(int n);

	int val()const{return vrednost;};

	static ListaSem allSems;
	static void tick();
	void deblock();
private:
	int vrednost;
	Red waitOnSem;
};

#endif
