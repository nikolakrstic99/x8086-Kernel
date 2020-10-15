#ifndef EVENT_H_
#define EVENT_H_
#include "IVTEntry.h"
#include "Const.h"

class KernelEv;

class Event {

public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();

protected:
 friend class KernelEv;
 void signal(); // can call KernelEv

private:
 KernelEv* myImpl;
};


#endif /* EVENT_H_ */
