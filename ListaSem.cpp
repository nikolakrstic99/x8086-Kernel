#include "Const.h"
#include "ListaSem.h"

ListaSem::ListaSem() {
	first = last = 0;
	n = 0;
}

int ListaSem::size() const { return n; }

void ListaSem::push(KernelSem *kersem) {
lock();
	last = (!first ? first : last->next) = new ListaSem::Elem(kersem, last);
	n++;
unlock();
}

void ListaSem::pop(KernelSem *ks) {
	Elem *cur = first,*prev=0;
	while(cur && cur->sem != ks) {
		prev=cur;
		cur = cur->next;
	}


	if(!cur) return;

lock();
	if (prev) prev->next = cur->next;
	else first = cur->next;
	if(cur == last) last = prev;
	n--;
	delete cur;
unlock();

}

ListaSem::~ListaSem() {
	while(first) {
		last = first;
		first = first->next;
		delete last;
	}
	first = last = 0;
	n = 0;
}

KernelSem* ListaSem::getSem(){
	if(n == 0) return 0;
			Elem *cur = first;

		lock();
			first = first->next; n--;
		unlock();

			cur->next = 0;
			return cur->sem;
}



