#include "common.h"

#define ACTIVATION_PER_SECOND 3
int startSimulationSemId;

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

void choseAndSignal();

