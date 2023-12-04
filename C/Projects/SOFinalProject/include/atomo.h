#include "common.h"
#include <time.h>

#define ATOM_MSG_LEN 6 + 8 /*6 char msg + 8byte msg type */
#define N_ATOM_QUEUE_KEY 0x222222
#define MASTER_QUE_TYPE 1

int startSimulationSemId;
int nAtomQueue;

void init();
void ready();
void waitForParentStartSimulation();
void checkForMsg();