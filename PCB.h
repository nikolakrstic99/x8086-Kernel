#ifndef PCB_H_
#define PCB_H_
#include "Const.h"
#include "thread.h"
#include "List.h"
#include "ListaPCB.h"

class PCB {
public:
	static int nextId;
	unsigned *stack;
	unsigned sp;
	unsigned ss;
	unsigned bp;
	Time timeSlice;
	ID id;
	int status;
	int waitOrNo;
	int timeToWait;

	Thread *myThread;
	static List<PCB*> allPCBs;
	ListaPCB waitingForMe;
	static PCB *running;
	static PCB *special;

	PCB(StackSize ,Time ,Thread *);
	~PCB();

	ID getId(){
		return id;
	};
	static ID getRunningId(){
		return PCB::running->id;
	};
	void start();
	void waitToComplete();
	static void wrapper();


	static Thread* getThreadById(int id){
		lock();
			for(int i=0;i<allPCBs.size();i++){
				if(allPCBs.get(i)->getId()==id)
					return allPCBs.get(i)->myThread;
			}
		unlock();
		return 0;
	}

};


#endif /* PCB_H_ */
