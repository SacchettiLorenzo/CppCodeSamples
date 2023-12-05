#include "../include/atomo.h"
struct sembuf sops;
int startSimulationSemId;

int natom;

int masterPid = 0;
siginfo_t si;

char writeBuffer[20];
struct AtomMsgbuf
{
    long mtype;
    char mtext[ATOM_MSG_LEN];
};
struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;
struct itimerspec checkMsgTimer;
timer_t checkmsgtimer;
struct sigevent sigalarm;

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
    masterPid = getppid();
    if (masterPid == 0)
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
    snprintf(AtomMsgSnd.mtext,ATOM_MSG_LEN,"%d", getpid());
 
    AtomMsgSnd.mtype = MASTER_QUE_TYPE;
    msgsnd(nAtomQueue, &AtomMsgSnd, ATOM_MSG_LEN, 0);

    /*SECTION - timer*/
    /*TODO - check if everything is necessary*/
    sigalarm.sigev_notify = SIGEV_SIGNAL;
    sigalarm.sigev_signo = SIGUSR1;
    sigalarm.sigev_value.sival_ptr = &checkmsgtimer;
    timer_create(CLOCK_REALTIME, &sigalarm, &checkmsgtimer);
    checkMsgTimer.it_value.tv_sec = 0;
    checkMsgTimer.it_value.tv_nsec = 500000000;
    checkMsgTimer.it_interval = checkMsgTimer.it_value;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);

}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    /*write(1, "atomo ready\n", 12);*/
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
        write(1, "Atomo Handling SIGINT\n", 22);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        checkForMsg();
        break;

    default:
        break;
    }
}

void checkForMsg()
{
    if (msgrcv(nAtomQueue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
        natom = atoi(AtomMsgRcv.mtext);
        /*snprintf(writeBuffer,20,"natom: %d", natom);
        write(1,writeBuffer,20);*/
        checkMsgTimer.it_value.tv_nsec = 0;
        timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);
        ready();
    }
}