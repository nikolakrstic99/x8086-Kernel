#ifndef _kernelev_h_
#define _kernelev_h_
#include "Const.h"

class PCB;

class KernelEv {
private:
	IVTNo ivt;
	int sem;
	PCB* vlasnik;
	PCB* blokiran;

	void block();
	void deblock();

public:
	KernelEv(IVTNo ivtno);
	~KernelEv();
	static KernelEv* arrayOfEvents[256];

	void wait();
	void signal();
};

#endif
