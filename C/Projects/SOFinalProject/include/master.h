#include "common.h"
#include <math.h>
#include <time.h>

#define N_ATOM_MAX 300
#define ATOM_MSG_LEN 6 + 8 /*6 char msg + 8byte msg type */

#define N_ATOM_QUEUE_KEY 0x222222
#define MASTER_QUE_TYPE 1

int totalChild = N_ATOMI_INIT + 2;

struct childData{
    pid_t pid;
    processType type;
};

int startSimulationSemId;
int nAtomQueue;

void init();

void waitForChildReady();

void startSimulation();

int normalDistributionNumberGenerator();

void checkForMsg();
