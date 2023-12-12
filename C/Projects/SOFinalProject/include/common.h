#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef COMMON_H
#define COMMON_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <signal.h>
#include <time.h>
#include <math.h>

#define START_SIMULATION_SEM_KEY 0x111111
#define ID_READY 0 /*used to tell the parent that the child is ready to execute*/
#define ID_GO 1 /*used to tell the child to start execute*/
/*IPC Message Queue Key */
#define N_ATOM_QUEUE_KEY 0x222222
#define SHARED_MEM_KEY 0X333333

#define N_ATOMI_INIT 5
/*Attivatore, Alimentazioni, Inibitore*/
#define N_SERVICE_PROCESS 3
#define START_SIMULATION_NUM_RES  N_ATOMI_INIT + N_SERVICE_PROCESS

#define WRITE_BUFFER_LEN 64

/*max nAtomo to generate*/
#define N_ATOM_MAX 300

/*  Lenght of the message that deliver nAtom
*   6 char msg + 8byte msg type 
*/
#define ATOM_MSG_LEN 6 + 8 

#define TEST_ERROR    if (errno) {fprintf(stderr, \
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}

typedef enum {false,true} bool;

static struct sigaction sa;

typedef enum {Master,Atomo,Attivatore,Alimentazione,Inibitore} processType;
static char* colors[5] = {
	"91m","92m","96m","33m","93m"
};

struct AtomMsgbuf
{
    long mtype;
    char mtext[ATOM_MSG_LEN];
};

struct SharedMemHeader{
	int version;
	int n_atomi;
	bool simulation;
};

struct Atomo{
    pid_t pid;
    int nAtom;
    pid_t masterPid;
    pid_t parentPid;
    bool scoria;
    bool inibito;
};

struct SharedMemory{
	struct SharedMemHeader SMH;
	struct Atomo* atomi;
};

static char precolor[5] = "\033[";
static char blank[7] = "\033[0m";

static char writeBuffer[WRITE_BUFFER_LEN];

void handle_signals(int signal,siginfo_t* info, void* v);

/*REVIEW - redefine this functions in each file to avoid that one process write with another one color*/
extern void Write(int fd, const void* buff, size_t len, processType pType);

/*
*   Generate a numer using Box Muller operation
*   the number in generated with a normal distributed probabilty
*/
int normalDistributionNumberGenerator(int n_atom_max);

#endif /* COMMON_H*/




