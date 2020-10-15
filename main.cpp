#include <stdio.h>
#include <dos.h>
#include <iostream.h>
#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.h"

volatile int cpuTime=0;
volatile int change=0;
volatile int lockCounter=0;
volatile int m=0;

void inic();

void restore();

int userMain(int argc, char** argv);
//PCB* main_PCB = new PCB(0,2,0);
//main_PCB->status=RUNNING;
//PCB::running = main_PCB;

//FILE *fp = fopen("out2.txt", "w");

int syncPrintf(const char *format, ...);

class ThreadB: public Thread {
public:
	ThreadB(int p,int o):Thread(p,o){}
    void run() {
        printf("\nUsli smo u B\n");
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	//cout<<"B:"<<i<<"\n";
            	printf("B:%d\n", i);
            	unlock();
            }
            for (int j = 0; j < 30000; j++);
        }
    }
    ~ThreadB(){waitToComplete();}
};



class ThreadC: public Thread {
public:	ThreadC(int p,int o):Thread(p,o){}
void run() {
    	lock();
        printf("\nUsli smo u C\n");
    	//cout<<"\nUsli smo u C\n";
    	unlock();
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("C:%d\n", i);
            	//cout<<"C:"<<i<<"\n";
            	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadC(){waitToComplete();}
};

class ThreadD: public Thread {
public:	ThreadD(int p,int o):Thread(p,o){}
void run() {
    	lock();
        //fprintf(fp,"\nUsli smo u D\n");
        cout<<"\nUsli smo u D\n";
        unlock();
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("D:%d\n", i);
            	//cout<<"D:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadD(){waitToComplete();}
};

class ThreadE: public Thread {
public:	ThreadE(int p,int o):Thread(p,o){}
 void run() {
    	lock();
    	//fprintf(fp,"\nUsli smo u E\n");
        cout<<"\nUsli smo u E\n";
        unlock();
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("E:%d\n", i);
            	//cout<<"E:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadE(){waitToComplete();}
};



class ThreadF: public Thread {
public:	ThreadF(int p,int o):Thread(p,o){}
void run() {
    	lock();
    	//fprintf(fp,"\nUsli smo u F\n");
        cout<<"\nUsli smo u F\n";
        unlock();
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("F:%d\n", i);
            	//cout<<"F:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadF(){waitToComplete();}
};



class ThreadG: public Thread {
public:	ThreadG(int p,int o):Thread(p,o){}
protected:void run() {
    	//fprintf(fp,"\nUsli smo u G\n");
    	cout<<"\nUsli smo u G\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
            	cout<<"G:"<<i<<"\n";
            	//fprintf(fp, "G:%d\n", i);
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

class ThreadH: public Thread {
	ThreadH(int p,int o):Thread(p,o){}
    void run() {
        //fprintf(fp,"\nUsli smo u H\n");
    	cout<<"\nUsli smo u H\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
            	cout<<"H:"<<i<<"\n";
            	//fprintf(fp, "H:%d\n", i);
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

class ThreadI: public Thread {
    void run() {
        //fprintf(fp,"\nUsli smo u I\n");
    	cout<<"\nUsli smo u I\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
                //fprintf(fp, "I:%d\n", i);
            	cout<<"I:"<<i<<"\n";
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

class ThreadJ: public Thread {
public:
	ThreadJ(int p,int o):Thread(p,o){}
    void run() {
        printf("\nUsli smo u B\n");
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	//cout<<"B:"<<i<<"\n";
            	printf("B:%d\n", i);
            	unlock();
            }
            for (int j = 0; j < 30000; j++);
        }
    }
    ~ThreadJ(){waitToComplete();}
};



class ThreadK: public Thread {
public:	ThreadK(int p,int o):Thread(p,o){}
void run() {
    	lock();
        printf("\nUsli smo u C\n");
    	//cout<<"\nUsli smo u C\n";
    	unlock();
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("C:%d\n", i);
            	//cout<<"C:"<<i<<"\n";
            	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadK(){waitToComplete();}
};

class ThreadL: public Thread {
public:	ThreadL(int p,int o):Thread(p,o){}
void run() {
    	lock();
        //fprintf(fp,"\nUsli smo u D\n");
        cout<<"\nUsli smo u D\n";
        unlock();
        for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("D:%d\n", i);
            	//cout<<"D:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadL(){waitToComplete();}
};

class ThreadM: public Thread {
public:	ThreadM(int p,int o):Thread(p,o){}
 void run() {
    	lock();
    	//fprintf(fp,"\nUsli smo u E\n");
        cout<<"\nUsli smo u E\n";
        unlock();
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("E:%d\n", i);
            	//cout<<"E:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadM(){waitToComplete();}
};



class ThreadN: public Thread {
public:	ThreadN(int p,int o):Thread(p,o){}
void run() {
    	lock();
    	//fprintf(fp,"\nUsli smo u F\n");
        cout<<"\nUsli smo u F\n";
        unlock();
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0){
            	lock();
            	printf("F:%d\n", i);
            	//cout<<"F:"<<i<<"\n";
               	unlock();
            }
            for (int j = 0; j < 30000; j++)
                ;
        }
    }

    ~ThreadN(){waitToComplete();}
};



class ThreadO: public Thread {
public:	ThreadO(int p,int o):Thread(p,o){}
protected:void run() {
    	//fprintf(fp,"\nUsli smo u G\n");
    	cout<<"\nUsli smo u G\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
            	cout<<"G:"<<i<<"\n";
            	//fprintf(fp, "G:%d\n", i);
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

class ThreadP: public Thread {
	ThreadP(int p,int o):Thread(p,o){}
    void run() {
        //fprintf(fp,"\nUsli smo u H\n");
    	cout<<"\nUsli smo u H\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
            	cout<<"H:"<<i<<"\n";
            	//fprintf(fp, "H:%d\n", i);
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

class ThreadR: public Thread {
    void run() {
        //fprintf(fp,"\nUsli smo u I\n");
    	cout<<"\nUsli smo u I\n";
    	for (int i = 0; i < 30000; i++) {
            if (i % 1000 == 0)
                //fprintf(fp, "I:%d\n", i);
            	cout<<"I:"<<i<<"\n";
            for (int j = 0; j < 30000; j++)
                ;
        }
    }
};

int main(int argc, char* argv[]) {

#ifndef BCC_BLOCK_IGNORE
    asm sti;
#endif


    inic();
	int r=userMain(argc,argv);
	delete PCB::running;
	delete PCB::special;
	restore();
};
