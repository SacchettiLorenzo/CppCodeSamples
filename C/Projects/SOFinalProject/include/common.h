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
#include <signal.h>

#define START_SIMULATION_SEM_KEY 0x111111
#define ID_READY 0 /*used to tell the parent that the child is ready to execute*/
#define ID_GO 1 /*used to tell the child to start execute*/
#define START_SIMULATION_NUM_RES 2

#define N_ATOMI_INIT 5

#define WRITE_BUFFER_LEN 64

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


static char precolor[5] = "\033[";
static char blank[7] = "\033[0m";

static char writeBuffer[WRITE_BUFFER_LEN];

void handle_signals(int signal,siginfo_t* info, void* v);

/*REVIEW - redefine this functions in each file to avoid that one process write with another one color*/
extern void Write(int fd, const void* buff, size_t len, processType pType);

#endif /* COMMON_H*/




