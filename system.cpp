#include <dos.h>
#include <stdio.h>
#include "Const.h"
#include "PCB.h"
#include "thread.h"
#include "special.h"
void lock(){
	lockCounter++;
	return;
};

void unlock(){
	if(lockCounter!=0)
		lockCounter--;
};
