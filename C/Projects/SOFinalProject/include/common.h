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
#define START_SIMULATION_NUM_RES  2 /*ID_READY ID_GO*/
#define ID_READY 0 /*used to tell the parent that the child is ready to execute*/
#define ID_GO 1 /*used to tell the child to start execute*/

#define SHARED_MEM_SEM_KEY 0X111112
#define SHARED_MEM_NUM_RES 1
#define ID_READ_WRITE 0


/*IPC Message Queue Keys */
#define N_ATOM_QUEUE_KEY 0x222221

/*IPC Shared Memory Keys*/
#define SHARED_MEM_KEY 0X333331

#define N_ATOMI_INIT 5
#define N_ATOM_MAX 10000

#define N_SERVICE_PROCESS 3	/*Attivatore, Alimentazioni, Inibitore*/

#define WRITE_BUFFER_LEN 64

/*max nAtomo to generate*/
#define NATOM_MAX 3000

/*  Lenght of the message that deliver nAtom
*   6 char msg + 8 byte mtype 
*/
#define ATOM_MSG_LEN 6 + 8 

#define RADOM_MSG_LEN 4 + 8 /*numbers from 0 to 1000 (4 chat) + 8 byte mtype*/

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
    pid_t masterPid;
	int ATTIVATORE;
	int ENERGIA_PRODOTTA;
	int ENERGIA_CONSUMATA;
	int ENERGIA_ASSORBITA;
	char lastInibition[100];/*ultima operazione di bilanciamento*/
};

struct Atomo{
    pid_t pid;
    int nAtom;/*NOTE - nAtom is a private information and should not be in the shared memory */
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

/*REVIEW - check if extern in necessary */
extern void Write(int fd, const void* buff, size_t len, processType pType);


/*
*   Generate a numer using Box Muller operation
*   the number in generated with a normal distributed probabilty
*/
int normalDistributionNumberGenerator(int n_atom_max);



#endif /* COMMON_H*/




