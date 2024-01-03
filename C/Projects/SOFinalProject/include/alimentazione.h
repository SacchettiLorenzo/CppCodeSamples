#include "common.h"

int STEP;
int N_NUOVI_ATOMI;
int N_ATOM_MAX; 
int NATOM_MAX; 



/*
* Initialization of.
* -signal handler
* -IPC 
*/
void init(int argc, char *argv[]);

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
* generate N_NUOVI_ATOMI every STEP seconds
*/
void generateNewAtoms();
