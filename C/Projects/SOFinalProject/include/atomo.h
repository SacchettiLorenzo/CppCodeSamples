#include "common.h"
#include <time.h>

/*IPC Message Queue type the atom use for sending*/
#define MASTER_QUE_TYPE 1

#define ACTIVATION_PROBABILTY 0.9


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
*/
void ready();

/*
* check the message queue for nAtom message
*/
void checkForMsg();

void split();
void setUpdateSharedMemory();
/*
void lookForSharedmemoryPosition();
void getUpdateSharedMemory();
*/
