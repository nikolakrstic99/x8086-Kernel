#ifndef RED_H_
#define RED_H_
#include "Const.h"

class PCB;
class KernelSem;

class Red {
public:
	struct Elem {
		PCB *pcb;

		Elem *next;

		Elem(PCB* p);
	};
	Elem *first, *last;
	int length;

	Elem* get();
	PCB* getPCB();
	int size() const{return length;};

	Red();
	~Red();
	void pop(Elem *e);
	void push(Elem *e);

};

#endif /* RED_H_ */

