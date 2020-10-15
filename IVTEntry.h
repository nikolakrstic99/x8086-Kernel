#ifndef _ivtentry_h_
#define _ivtentry_h_
#include "Const.h"
#include "KernelEv.h"


class IVTEntry {
public:
	IVTEntry(IVTNo ivtno, pInterrupt inter);
	~IVTEntry();

	void signal();
	void old();

private:
	pInterrupt oldRoutine;
	IVTNo ivt;
	static IVTEntry* allEntries[256];

};

#endif
