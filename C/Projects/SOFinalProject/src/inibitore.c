#include "../include/inibitore.h"

struct sembuf sops;
int startSimulationSemId;
int sharedMemorySemId;
int shared_mem_id;
struct SharedMemory *SM;
int masterPid;
int main(int argc, char *argv[])
{
    init();
    ready();
    waitForParentStartSimulation();

    /*TODO - select ATOM_INIBITION_NUMBER atoms and cgange the value in the shared memory*/

    while (1)
    {
        pause();
    }
}

void init()
{
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

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

    masterPid = SM->SMH.masterPid;
    /*-------------------------------------------*/

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Inibitore ready\n", 17, Inibitore);
}

void waitForParentStartSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = -1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Inibitore start simulation\n", 29, Inibitore);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Inibitore Handling SIGINT\n", 27, Inibitore);
        exit(EXIT_SUCCESS);
        break;

    default:
        break;
    }
}