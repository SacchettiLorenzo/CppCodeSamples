#include "../include/attivatore.h"

struct sembuf sops;
int startSimulationSemId;
int shared_mem_id;
int sharedMemorySemId;
struct SharedMemory *SM;
int random;
int main(int argc, char *argv[])
{
    init();
    ready();
    pause();
}

void init()
{
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);

    /*Shared Memory SEM -------------------------*/
    sharedMemorySemId = semget(SHARED_MEM_SEM_KEY, SHARED_MEM_NUM_RES, 0600 | IPC_CREAT);
    semctl(sharedMemorySemId, 0, SETVAL, 1);
    /*-------------------------------------------*/

    /*Shared Memory -----------------------------*/
    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + N_ATOM_MAX * sizeof(struct Atomo), 0600 | IPC_CREAT);
    if (shared_mem_id == -1)
    {
        Write(1, "Error creating shared memory segment\n", 36, Master);
        TEST_ERROR;
    }
    SM = shmat(shared_mem_id, NULL, 0);
    /*-------------------------------------------*/
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Attivatore ready\n", 17,Attivatore);
    waitForParentStartSimulation();
}

void waitForParentStartSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = -1;
    semop(startSimulationSemId, &sops, 1);
}

void handle_signals(int signal,siginfo_t* info, void* v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Attivatore Handling SIGINT\n", 27,Attivatore);
        exit(EXIT_SUCCESS);
        break;

    default:
        break;
    }
}

void choseAndSignal(int max){
    /*
    send x random number in a totalaly new message queue
    send a signal to a random atom
    the atom will check if the first number fit the split requirement (to be decided)
    if fit the atom will split, if not wont
    in this way the splitting should be brobabilistic and safe
    */

}