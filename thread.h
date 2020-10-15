#ifndef THREAD_H_
#define THREAD_H_
#include "Const.h"
#include <dos.h>
#include <iostream.h>

class PCB; // Kernel's implementation of a user's thread

class Thread {

public:
 void start();
 void waitToComplete();
 virtual ~Thread();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);

protected:
 friend class PCB;
 Thread (StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
 virtual void run(){};
public:
 PCB* myPCB;
};
void dispatch ();


#endif /* THREAD_H_ */
