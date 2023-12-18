#include "common.h"
#include <time.h>

/*IPC Message Queue type the atom use for sending*/
#define MASTER_QUE_TYPE 1

#define ACTIVATION_PROBABILTY 0.9

#define MIN_N_ATOMICO 10


/*
* Initialization of.
* -signal handler
* -IPC 
* -Get nAtom
*/
void init();

/*
* operating on the ID_READY semaphore 
* tell the master that ther process is ready
* but only if the atom is a direct child of the master
*/
void ready();

/*
* check the message queue for nAtom message
*/
void checkForMsg();

/*
* spli and generate a new atom
*/
void split();

/*
* update the data on the shared memory
*/
void setUpdateSharedMemory();

/*
* calculate energy from the splitting using provided equation
*/
int calculateEnergy(int nAtom1, int nAtom2);