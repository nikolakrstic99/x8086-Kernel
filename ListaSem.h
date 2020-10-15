#ifndef LISTASEM_H_
#define LISTASEM_H_
#include "Const.h"

class KernelSem;

class ListaSem {
private:
	struct Elem {
		KernelSem *sem;
		Elem *next;
		Elem(KernelSem *kersem,Elem *nn=0) {
			sem = kersem;
			next = nn;
		};
	};

	Elem *first, *last;
	int n;
public:
	friend class KernelSem;
	ListaSem();
	~ListaSem();
	KernelSem* getSem();
	int size() const;
	void push(KernelSem *ks);
	void pop(KernelSem *ks);
};


#endif /* LISTASEM_H_ */
