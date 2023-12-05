#define _GNU_SOURCE
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

struct sigaction sa;

typedef enum {Master,Atomo,Attivatore,Alimentazione} processType;

void handle_signals(int signal,siginfo_t* info, void* v);

void Write(int fd, const void* buff, size_t len, processType pType);






#define TEST_ERROR    if (errno) {fprintf(stderr, \
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}
