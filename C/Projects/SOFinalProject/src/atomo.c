#include "../include/atomo.h"
struct sembuf sops;
int startSimulationSemId;

struct Atomo atomo;

int masterPid = 0;
siginfo_t si;

struct AtomMsgbuf
{
    long mtype;
    char mtext[ATOM_MSG_LEN];
};
struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;

struct sigevent sigalarm;

int startSimulationSemId;
int nAtomQueue;
bool is_N_Atom = false;

int main(int argc, char *argv[])
{
    init();
    waitForParentStartSimulation();
    while (1)
    {
        /* code */
    }
}

void init()
{
    
    atomo.pid = getpid();
    atomo.nAtom = 0;
    atomo.masterPid = getppid();

    if (atomo.masterPid == 0)
    {
        write(1, "cannot get master pid\n", 22);
        exit(EXIT_FAILURE);
    }

    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    nAtomQueue = msgget(N_ATOM_QUEUE_KEY, 0600);
    snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", getpid());

    AtomMsgSnd.mtype = MASTER_QUE_TYPE;
    msgsnd(nAtomQueue, &AtomMsgSnd, ATOM_MSG_LEN, 0);

    
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Atomo ready\n", 12, Atomo);
}

void waitForParentStartSimulation()
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
        if (is_N_Atom == false)
        {
            checkForMsg();
        }
        break;

    default:
        break;
    }
}

void checkForMsg()
{
    if (msgrcv(nAtomQueue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
         atomo.nAtom = atoi(AtomMsgRcv.mtext);
        if ( atomo.nAtom > 0)
        {
            is_N_Atom = true;
            snprintf(writeBuffer, 25 + strlen(AtomMsgRcv.mtext) + 6, "Atomo: %d got nAtom %d\n", getpid(),  atomo.nAtom);
            Write(1, writeBuffer, 19 + strlen(AtomMsgRcv.mtext) + 6, Atomo);
            ready();
        }
    }
}