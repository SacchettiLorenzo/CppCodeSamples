#include "common.h"
#include <time.h>

/*  Lenght of the message that deliver nAtom
*   6 char msg + 8byte msg type 
*/
#define ATOM_MSG_LEN 6 + 8 

/*IPC Message Queue Key */
#define N_ATOM_QUEUE_KEY 0x222222

/*IPC Message Queue type the atom use for sending*/
#define MASTER_QUE_TYPE 1




/*
* Initialization of.
* -signal handler
* -IPC 
*/
void init();

/*
* operating on the ID_READY semaphore 
* tell the master that ther process is ready
*/
void ready();

/*
* wait for the master to 
* start simulation using ID_GO
*/
void waitForParentStartSimulation();

/*
* check the message queue for nAtom message
*/
void checkForMsg();