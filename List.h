
#ifndef LIST_H_
#define LIST_H_
#include "Const.h"
#include "thread.h"
#include <iostream.h>

template<class T>
class List{
public:
	struct Elem{
		T pod;
		Elem *next,*prev;
		Elem(T data):pod(data),prev(0),next(0){}
	};
	int n;
	Elem *first,*last;

	List():first(0),last(0),n(0){};

	int size(){return n;};

	void push(T pod){				//na kraj liste
		lock();
		Elem* newelem=new Elem(pod);
		unlock();
		if (n>0) { newelem->prev = last; last->next = newelem; }
			else first = newelem;
		last = newelem;
		n++;
	};

	T pop(){
		T ret = first->pod;
		Elem *toDelete = first;
		first = first->next;
		n--;
		if (n>0) first->prev = 0;
			else first = last = 0;
		lock();
		delete toDelete;
		unlock();
		return ret;
	};

	void remove(T pod){
		Elem *cur=first;
		while(cur && cur->pod!=pod)cur=cur->next;
		if(!cur) return;

	lock();
		if(n==1){
			delete cur;
			unlock();
			return;
		}
		if(cur->prev) cur->prev->next = cur->next;
		if(cur->next) cur->next->prev = cur->prev;
		if(cur == first) first = first->next;
		if(cur == last) last = last->prev;
		n--;
		delete cur;
	unlock();
	}

	T get(int poz){
		if(poz>=n || poz<0)return 0;
		Elem *tmp=first;
		while(poz--)
			tmp=tmp->next;
		return tmp->pod;
	}
};

#endif /* LIST_H_ */
