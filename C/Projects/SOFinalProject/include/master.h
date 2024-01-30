#ifndef COMMON_H
#include "common.h"
#endif


/*IPC Message Queue type the master use for reading*/
#define MASTER_QUE_TYPE 1

int N_ATOMI_INIT;
int ENERGY_DEMAND;
int SIM_DURATION;
int ENERGY_EXPLODE_THRESHOLD;
int N_ATOM_MAX; 
int NATOM_MAX; 
int inibitore;

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
void init(int argc,char *argv[]);

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

/*
* send SINGINT to every process
* call dumpMemory()
* wait for all the process to terminate
* close all IPC channel
* close the master
*/
void stopSimulation();


