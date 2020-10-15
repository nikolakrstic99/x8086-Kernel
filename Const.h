#ifndef CONST_H_
#define CONST_H_
#define NEW 0;
#define READY 1;
#define RUNNING 2;
#define BLOCKED 3;
#define TERMINATED 4;
#define KILLED 5;
#define IVT_SIZE 256;

#define PREPAREENTRY(num, flag)\
	void interrupt inter##num(...);\
	IVTEntry newEntry##num(num,inter##num);\
	void interrupt inter##num(...){\
		newEntry##num.signal();\
		if(flag==1)\
			newEntry##num.old();\
	}

typedef unsigned char IVTNo;


typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
const StackSize maxStackSize = 65536;
const StackSize minStackSize = 64;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2; // default = 2*55ms
typedef int ID;


typedef void interrupt (*pInterrupt) (...);

extern volatile int lockCounter;
void lock();
void unlock();


#endif /* CONST_H_ */
