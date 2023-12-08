#include "../include/master.h"

int value;
int status;
struct ServiceProcessData service_process[N_SERVICE_PROCESS];
struct sembuf sops;
pid_t childPid;
int i;
char *args_0[] = {"./attivatore.out", (char*)0};
char *args_1[] = {"./alimentazione.out",(char*)0};
char *args_2[] = {"./inibitore.out", (char*)0};
char *args_3[] = {"./atomo.out", (char*)0};
double random1, random2;

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

int simulation_Sem;
int nAtom_Queue;

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
                Write(1, "calling Attivatore\n", 19, Master);
                if(execve(args_0[0], args_0, NULL) == -1){
                    Write(1,"Error calling Attivatore\n",25,Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i == 1)
            {
                Write(1, "calling Alimentazione\n", 22, Master);
                if(execve(args_1[0], args_1, NULL) == -1){
                    Write(1,"Error calling Alimentazione\n",28,Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i == 2)
            {
                Write(1, "calling Inibitore\n", 18, Master);
                if(execve(args_2[0], args_2, NULL) == -1){
                    Write(1,"Error calling Inibitore\n",24,Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i > 2)
            {
                Write(1, "calling Atomo\n", 14, Master);
                if(execve(args_3[0], args_3, NULL) == -1){
                    Write(1,"Error calling Atomo\n",20,Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            exit(EXIT_SUCCESS);
            break;

        default:
            if (i < N_SERVICE_PROCESS)
            {
                if (i == 0)
                {
                    (service_process + i)->type = Attivatore;
                }
                if (i == 1)
                {
                    (service_process + i)->type = Alimentazione;
                }
                if (i == 2)
                {
                    (service_process + i)->type = Inibitore;
                }
                (service_process + i)->pid = value;
            }

            break;
        }
    }

    waitForChildReady();

    {
        /*FIXME - chage with a single call to the process group*/
        waitpid((service_process + 0)->pid, &status, 0);
        waitpid((service_process + 1)->pid, &status, 0);
        waitpid((service_process + 2)->pid, &status, 0);
    }
        
    /*NOTE - master do not have to wait all the process but just the service_process*/
}

void init()
{
    srand(time(NULL));

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals; /*same as handler*/
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    simulation_Sem = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600 | IPC_CREAT);
    
    semctl(simulation_Sem, ID_READY, SETVAL, 0);
    semctl(simulation_Sem, ID_GO, SETVAL, 0);
    
    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600 | IPC_CREAT);

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

void waitForChildReady()
{
    sops.sem_num = ID_READY;
    sops.sem_op = -totalChild;
    sops.sem_flg = 0;
    /*write(1, "master wait for child ready\n", 28);*/
    semop(simulation_Sem, &sops, 1);
    /*write(1, "all process ready: starting simulation\n", 39);*/
}

void startSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = totalChild;
    semop(simulation_Sem, &sops, 1);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Master Handling SIGINT\n", 23, Master);

        semctl(simulation_Sem, 0, IPC_RMID);
        semctl(simulation_Sem, 0, IPC_RMID);

        msgctl(nAtom_Queue, IPC_RMID, NULL);

        killpg(getpid(), SIGINT);
        
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
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
        random1 = (double)rand() / (double)RAND_MAX;
        random2 = (double)rand() / (double)RAND_MAX;
        randomAtomNumber = abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
    }
    return randomAtomNumber;
}

void checkForMsg()
{
    checkMsgTimer.it_value.tv_nsec = 0;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);
    while (msgrcv(nAtom_Queue, &AtomMsgRcv, ATOM_MSG_LEN, MASTER_QUE_TYPE, 0) > 0)
    {
        AtomMsgSnd.mtype = (long)atoi(AtomMsgRcv.mtext);
        snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator());
        msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0);
        kill(AtomMsgSnd.mtype, SIGUSR1);
    }
    checkMsgTimer.it_value.tv_nsec = 500000000;
    timer_settime(checkmsgtimer, 0, &checkMsgTimer, NULL);
}