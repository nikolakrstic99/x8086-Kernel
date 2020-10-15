#ifndef SPECIAL_H_
#define SPECIAL_H_
#include "thread.h"

class Special:public Thread{
public:
	Special();
protected:
	void run();
};

#endif /* SPECIAL_H_ */
