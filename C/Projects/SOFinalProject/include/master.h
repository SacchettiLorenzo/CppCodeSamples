#ifndef COMMON_H
#include "common.h"
#endif


/*IPC Message Queue type the master use for reading*/
#define MASTER_QUE_TYPE 1

#define ENERGY_DEMAND 30

#define SIM_DURATION 200

#define ENERGY_EXPLODE_THRESHOLD 10000000

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
* dump shared memory into a file
*/
void dumpMemory();


