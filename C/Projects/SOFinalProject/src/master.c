#include "../include/master.h"

int value;
int status;
struct childData *childs;
struct sembuf sops;
pid_t childPid;
int i;
char *args_1[] = {"./attivatore.out"};
char *args_2[] = {"./alimentazione.out"};
char *args_3[] = {"./atomo.out"};
double r1, r2;

char writeBuffer[20];
struct AtomMsgbuf
{
    long mtype;
    char mtext[ATOM_MSG_LEN];
};
struct AtomMsgbuf AtomMsgRcv;
struct AtomMsgbuf AtomMsgSnd;

struct itimerspec checkMsgTimer;
timer_t checkmsgtimer;
struct sigevent sigalarm;

int main(int argc, char *argv[])
{
    normalDistributionNumberGenerator();
    init();
    for (i = 0; i < totalChild; i++)
    {
        switch (value = fork())
        {
        case -1:
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            if (i == 0)
            {
                write(1, "calling attivatore\n", 19);
                execve(args_1[0], args_1, NULL);
                exit(EXIT_SUCCESS);
                break;
            }
            if (i == 1)
            {
                write(1, "calling alimentazione\n", 22);
                execve(args_2[0], args_2, NULL);
                exit(EXIT_SUCCESS);
                break;
            }
            if (i > 1)
            {
                write(1, "calling atomo\n", 14);
                execve(args_3[0], args_3, NULL);
                exit(EXIT_SUCCESS);
                break;
            }
            exit(EXIT_SUCCESS);
            break;

        default:
            if (i == 0)
            {
                (childs + i)->type = Attivatore;
            }
            if (i == 1)
            {
                (childs + i)->type = Alimentazione;
            }
            if (i > 1)
            {
                (childs + i)->type = Atomo;
            }
            (childs + i)->pid = value;
            break;
        }
    }

    waitForChildReady();
    while ((childPid = wait(&status)) != -1)
    {
    }
}

void init()
{
    srand(time(NULL));
    childs = (struct childData *)malloc(totalChild * sizeof(struct childData));

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals; /*same as handler*/
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT | SIGALRM, &sa, NULL);

    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600 | IPC_CREAT);

    nAtomQueue = msgget(N_ATOM_QUEUE_KEY, 0600 | IPC_CREAT);
    

    /*SECTION - timer*/
    /*TODO - check if everything is necessary*/
    sigalarm.sigev_notify = SIGEV_SIGNAL;
    sigalarm.sigev_signo = SIGALRM;
    sigalarm.sigev_value.sival_ptr = &checkmsgtimer;
    timer_create(CLOCK_REALTIME, &sigalarm, &checkmsgtimer);
    checkMsgTimer.it_value.tv_sec = 0;
    checkMsgTimer.it_value.tv_nsec = 500000000;
    checkMsgTimer.it_interval = checkMsgTimer.it_value;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);

    semctl(startSimulationSemId, ID_READY, SETVAL, 0);
    semctl(startSimulationSemId, ID_GO, SETVAL, 0);
}

void waitForChildReady()
{
    sops.sem_num = ID_READY;
    sops.sem_op = -totalChild;
    sops.sem_flg = 0;
    /*write(1, "master wait for child ready\n", 28);*/
    semop(startSimulationSemId, &sops, 1);
    /*write(1, "all process ready: starting simulation\n", 39);*/
}

void startSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = totalChild;
    semop(startSimulationSemId, &sops, 1);
}

/*FIXME - SIGINT non funziona. Possibile soluzione: dividere gli handler in handler singoli e non comulativi*/
void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        write(1, "Master Handling SIGINT\n", 23);

        /*FIXME - semctl and msgctl are not doing what supposed to*/
        /*remove all semaphore with startSimulationSemId id - semnum ingored*/
        semctl(startSimulationSemId, 0, IPC_RMID);
        semctl(startSimulationSemId, 0, IPC_RMID);

        msgctl(nAtomQueue, IPC_RMID, NULL);

        /*send SIGINT to all the child process*/
        for (i = 0; i < totalChild; i++)
        {
            snprintf(writeBuffer,20,"%d", (childs + i)->pid);
            write(1,writeBuffer,20);
            kill((childs + i)->pid, SIGINT);
        }
        exit(EXIT_SUCCESS);
        break;
    case SIGALRM:
        checkForMsg();
        break;

    default:
        break;
    }
}

int normalDistributionNumberGenerator()
{
    int randomAtomNumber;
    /*Using Box-Muller Transformation*/
    while (randomAtomNumber < 1 || randomAtomNumber > N_ATOM_MAX)
    {
        r1 = (double)rand() / (double)RAND_MAX;
        r2 = (double)rand() / (double)RAND_MAX;
        randomAtomNumber = abs((int)(100 * (sqrt(-2 * log(r1)) * cos(2 * 3.14 * r2))));
    }

    return randomAtomNumber;
}

void checkForMsg()
{
    /*FIXME - it does not read*/
    checkMsgTimer.it_value.tv_nsec = 0;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);
    while (msgrcv(nAtomQueue, &AtomMsgRcv, ATOM_MSG_LEN, MASTER_QUE_TYPE, 0) > 0)
    {
        AtomMsgSnd.mtype = (long)atoi(AtomMsgRcv.mtext);
        snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator());
        msgsnd(nAtomQueue, &AtomMsgSnd, ATOM_MSG_LEN, 0);
    }
    checkMsgTimer.it_value.tv_nsec = 500000000;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);
}