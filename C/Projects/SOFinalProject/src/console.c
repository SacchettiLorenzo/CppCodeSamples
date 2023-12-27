#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define CONSOLE_QUEUE_KEY 0X222222
#define SHARED_MEM_KEY 0X333331

#define COMMAND_LEN 20

#define SHARED_MEM_SEM_KEY 0X111112
#define SHARED_MEM_NUM_RES 1
#define ID_READ_WRITE 0

#define TEST_ERROR                                    \
    if (errno)                                        \
    {                                                 \
        fprintf(stderr,                               \
                "%s:%d: PID=%5d: Error %d (%s) %s\n", \
                __FILE__,                             \
                __LINE__,                             \
                getpid(),                             \
                errno,                                \
                strerror(errno),                      \
                strerrorname_np(errno));              \
    }

typedef enum
{
    false,
    true
} bool;

/*MISC*/
int try = 10;
int i;
pid_t masterPid = 0;
pid_t inibitorePid = 0;
int selection1;
char command[COMMAND_LEN];

char commands[5][COMMAND_LEN] = {
    "help", "sim_start", "sim_end", "inibitore_on", "inibitore_off"};

/*SEMAPHORES*/
struct sembuf sops;
int sharedMemorySemId;

/*SHARED MEMORY*/
int shared_mem_id;
struct SharedMemHeader
{
    int n_atomi;
    bool simulation;
    bool inibitore;
    pid_t masterPid;
    pid_t inibitorePid;
    int ATTIVAZIONI;
    int ENERGIA_PRODOTTA;
    int ENERGIA_CONSUMATA;
    int ENERGIA_ASSORBITA;
    int scorie;
};
struct SharedMemHeader *SMH;

/*FUNCTIONS*/
void readKeyboard();
void helpMenu();
void startSimulation();

int main(int argc, char *argv[])
{
    /*Shared Memory SEM -------------------------*/
    sharedMemorySemId = semget(SHARED_MEM_SEM_KEY, SHARED_MEM_NUM_RES, 0600);
    /*-------------------------------------------*/

    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader), 0600);
    if (shared_mem_id == -1)
    {
        write(1, "error getting shared memory\n", 29);
    }
    SMH = shmat(shared_mem_id, NULL, 0);
    masterPid = SMH->masterPid;
    inibitorePid = SMH->inibitorePid;

    /*
    if (system("clear") == -1)
    {
        write(1, "cannot clear\n", 13);
    }
    */

    if (masterPid == 0)
    {
        printf("insert master pid\n");
        scanf("%d", &masterPid);
    }

    if (inibitorePid == 0)
    {
        printf("insert inibitore pid\n");
        scanf("%d", &inibitorePid);
    }

    while (1)
    {
        readKeyboard();
    }
}

void readKeyboard()
{
    scanf("%s", command);

    if (strcmp(command, commands[0]) == 0)
    {
        helpMenu();
        return;
    }

    if (strcmp(command, commands[1]) == 0)
    {
        kill(masterPid, SIGUSR2);
        return;
    }

    if (strcmp(command, commands[2]) == 0)
    {

        kill(masterPid, SIGINT) == -1;

        return;
    }
    /*inibitore_on*/
    if (strcmp(command, commands[3]) == 0)
    {
        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        semop(sharedMemorySemId, &sops, 1);
        kill(SMH->inibitorePid, SIGCONT) == -1;
        SMH->inibitore = true;
        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = 1;
        semop(sharedMemorySemId, &sops, 1);
        return;
    }
    /*inibitore_off*/
    if (strcmp(command, commands[4]) == 0)
    {
        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        semop(sharedMemorySemId, &sops, 1);
        kill(SMH->inibitorePid, SIGSTOP) == -1;
        SMH->inibitore = false;
        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = 1;
        semop(sharedMemorySemId, &sops, 1);
        return;
    }

    write(1, "unknow command\n", 15);
    return;
}

void helpMenu()
{
    write(1, "help menu\n", 11);
}

void startSimulation()
{
}