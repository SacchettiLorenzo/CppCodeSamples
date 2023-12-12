#ifndef COMMON_H
#include "common.h"
#endif

/*  Lenght of the message that deliver nAtom
*   6 char msg + 8byte msg type 
*/
#define ATOM_MSG_LEN 6 + 8 

/*IPC Message Queue Key */
#define N_ATOM_QUEUE_KEY 0x222222
/*IPC Message Queue type the master use for reading*/
#define MASTER_QUE_TYPE 1

/*Attivatore, Alimentazioni, Inibitore*/
#define N_SERVICE_PROCESS 3



struct ServiceProcessData{
    pid_t pid;
    processType type;
};



/*
* Initialization of.
* -radnom
* -signal handler
* -IPC 
* -timer
*/
void init();

/*
* wait for all the child process to
* set ID_READY
*/
void waitForChildReady();

/*
* operating on the ID_GO semaphore 
* start the simulation
*/
void startSimulation();

/*  
*   check the queue for nAtom requet,
*   if requested send nAtom,
*/
void checkForMsg();
