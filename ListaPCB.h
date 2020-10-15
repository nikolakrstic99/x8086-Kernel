#ifndef LISTAPCB_H_
#define LISTAPCB_H_

class PCB;

class ListaPCB{
private:
	struct Elem {
		PCB *pcb;
		Elem *next;
		Elem(PCB *p,Elem *nn=0) {
			pcb = p;
			next = nn;
		};
	};

	Elem *first, *last;
	int n;
public:
	friend class PCB;
	ListaPCB();
	~ListaPCB();
	PCB* getPCB();
	int size() const;
	void push(PCB *p);
	void pop(PCB *p);
};



#endif /* LISTAPCB_H_ */
