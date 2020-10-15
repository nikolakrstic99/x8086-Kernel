#include <dos.h>
#include "Const.h"
#include "IVTEntry.h"
#include "KernelEv.h"


IVTEntry* IVTEntry::allEntries[256] = {0};

IVTEntry::IVTEntry(IVTNo ivtno, pInterrupt inter):ivt(ivtno),oldRoutine(0) {
	IVTEntry::allEntries[ivtno] = this;
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	oldRoutine = getvect(ivtno);
	setvect(ivtno, inter);
	asm sti;
#endif

}

IVTEntry::~IVTEntry() {
	IVTEntry::allEntries[ivt] = 0;
#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(ivt, oldRoutine);
	asm sti;
#endif
}

void IVTEntry::signal() {
	if(KernelEv::arrayOfEvents[ivt] != 0) {
		KernelEv::arrayOfEvents[ivt]->signal();
	}
}

void IVTEntry::old() {
	if(oldRoutine == 0)
		return;
	(*oldRoutine)();
}
