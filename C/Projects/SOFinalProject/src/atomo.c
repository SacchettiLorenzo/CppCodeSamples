#include "../include/atomo.h"
struct sembuf sops;
int startSimulationSemId;

struct Atomo atomo;

int masterPid = 0;
siginfo_t si;

struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;

struct sigevent sigalarm;

int startSimulationSemId;
int nAtom_Queue;

int value;
char *args_0[] = {"./atomo.out", (char *)0};

int shared_mem_id;

struct SharedMemory* SM;

int main(int argc, char *argv[])
{
    init();

    waitForMasterStartSimulation();

    pause();
}

void init()
{

    atomo.pid = getpid();
    atomo.nAtom = 0;
    atomo.masterPid = getppid();

/*
    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + N_ATOMI_INIT*sizeof(struct Atomo), 0600| IPC_CREAT);
    shmctl(shared_mem_id, IPC_RMID, NULL);
    SM = (struct SharedMemory*)shmat(shared_mem_id, NULL, 0);
*/

    if (atomo.masterPid == 0)
    {
        Write(1, "cannot get master pid\n", 22, Atomo);
        exit(EXIT_FAILURE);
    }

    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600);

    if (msgrcv(nAtom_Queue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
        atomo.nAtom = atoi(AtomMsgRcv.mtext);
        if (atomo.nAtom > 0)
        {
            snprintf(writeBuffer, 25 + strlen(AtomMsgRcv.mtext) + 6, "Atomo: %d got nAtom %d\n", getpid(), atomo.nAtom);
            Write(1, writeBuffer, 19 + strlen(AtomMsgRcv.mtext) + 6, Atomo);
            ready();
        }
    }
}

void ready()
{
    /*FIXME -
    if splitted atom this operation is useless
    */
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Atomo ready\n", 12, Atomo);
}

void waitForMasterStartSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = -1;
    semop(startSimulationSemId, &sops, 1);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Atomo Handling SIGINT\n", 22, Atomo);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        split();
        break;

    default:
        pause();
        break;
    }
}

void split()
{
    switch (value = fork())
    {
    case -1:
        Write(1, "Error splitting Atomo\n", 22, Atomo);
        TEST_ERROR;
        break;
    case 0:

        if (execve(args_0[0], args_0, NULL) == -1)
        {
            Write(1, "Error splitting Atomo\n", 22, Atomo);
            TEST_ERROR;
            exit(EXIT_FAILURE);
        }

        break;

    default:
        AtomMsgSnd.mtype = value;
        snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator(0));
        if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
        {
            Write(1, "Error sending message\n", 22, Atomo);
            TEST_ERROR;
        }
        break;
    }
}
