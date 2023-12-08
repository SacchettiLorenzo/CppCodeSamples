#include "../include/attivatore.h"

struct sembuf sops;
int startSimulationSemId;
int main(int argc, char *argv[])
{
    init();
    ready();
}

void init()
{
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

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