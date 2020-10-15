#include "PCB.h"
#include "Const.h"
#include "KerSem.h"
#include "Red.h"

Red::Elem::Elem(PCB* p):pcb(p),next(0){

}

Red::Red(): length(0),first(0),last(0){

}

void Red::push(Elem *e) {
lock();
	last = (!first ? first : last->next) = e;
	length++;
unlock();
}

Red::Elem* Red::get() {
	lock();
	if(length == 0) return 0;
	Elem *ret = first;

	first = first->next; length--;

	ret->next = 0;
	unlock();
	return ret;
}

PCB* Red::getPCB(){
	return get()->pcb;
}

void Red::pop(Elem *e) {

	Elem *cur = first, *prev = 0;
	while(cur && cur != e) {
		prev = cur;
		cur = cur->next;
	}
	if(!cur) return;

lock();
	if(prev) prev->next = cur->next;
	else first = cur->next;

	if(cur == last) last = prev;
	length--;
unlock();
}

Red::~Red() {
	while(first) {
		last = first;
		first = first->next;
		delete last;
	}
	first = last = 0;
	length = 0;
}




