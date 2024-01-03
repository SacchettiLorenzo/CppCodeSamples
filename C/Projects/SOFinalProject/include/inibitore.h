#include "common.h"

int N_ATOM_MAX; 
int NATOM_MAX; 
int ENERGY_EXPLODE_THRESHOLD;
int ENERGY_ABSORPTION;
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

int calculateEnergy(int nAtom1, int nAtom2);