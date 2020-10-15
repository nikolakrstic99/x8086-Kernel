#include "Const.h"
#include "ListaPCB.h"

ListaPCB::ListaPCB() {
	first = last = 0;
	n = 0;
}

int ListaPCB::size() const { return n; }

void ListaPCB::push(PCB* p) {
lock();
	last = (!first ? first : last->next) = new ListaPCB::Elem(p, last);
	n++;
unlock();
}

void ListaPCB::pop(PCB *p) {
	Elem *cur = first,*prev=0;
	while(cur && cur->pcb != p) {
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

ListaPCB::~ListaPCB() {
	while(first) {
		last = first;
		first = first->next;
		delete last;
	}
	first = last = 0;
	n = 0;
}

PCB* ListaPCB::getPCB(){
	if(n == 0) return 0;
			Elem *cur = first;

		lock();
			first = first->next; n--;
		unlock();

			cur->next = 0;
			return cur->pcb;
}

