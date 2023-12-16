#include "../include/alimentazione.h"

struct sembuf sops;

struct itimerspec atomGenerationTimer;
timer_t atomgenerationtimer;
struct sigevent sigusr;
struct AtomMsgbuf AtomMsgSnd;

int startSimulationSemId;
int i;
char *args_0[] = {"./atomo.out", (char *)0};
int value;
int nAtom_Queue;
char buff[40];
int main(int argc, char *argv[])
{
    init();
    ready();
    waitForParentStartSimulation();

    while (1)
    {
        pause();
    }
}

void init()
{
    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600 | IPC_CREAT);
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    /*FIXME - THIS timer SHOULD START AFTER MASTER START SIMULATION*/
    /*SECTION - timer*/
    /*TODO - check if everything is necessary and change name*/
    /*sigalarm.sigev_notify = SIGEV_SIGNAL;*/
    sigusr.sigev_signo = SIGUSR1;
    sigusr.sigev_value.sival_ptr = &atomgenerationtimer;
    timer_create(CLOCK_REALTIME, &sigusr, &atomgenerationtimer);
    atomGenerationTimer.it_value.tv_sec = STEP;
    atomGenerationTimer.it_value.tv_nsec = 0;
    atomGenerationTimer.it_interval = atomGenerationTimer.it_value;
    timer_settime(atomgenerationtimer, 0, &atomGenerationTimer, NULL);
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Alimentazione ready\n", 20, Alimentazione);
}

void waitForParentStartSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = -1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Alimentazione start simulation\n", 31, Alimentazione);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Alimentazione Handling SIGINT\n", 30, Alimentazione);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        Write(1, "Alimentazione generate new atoms\n", 33, Alimentazione);
        generateNewAtoms();
        break;

    default:
        break;
    }
}

void generateNewAtoms()
{
    for (i = 0; i < N_NUOVI_ATOMI; i++)
    {
        switch (value = fork())
        {
        case -1:
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            Write(1, "calling Atomo\n", 14, Alimentazione);
            if (execve(args_0[0], args_0, NULL) == -1)
            {
                Write(1, "Error calling Atomo\n", 20, Master);
                TEST_ERROR;
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
            break;
        default:
            AtomMsgSnd.mtype = value;
            snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator(0));
            bzero(buff, 40);
            snprintf(buff, 40, "alim create atom %d with %d\n", value, atoi(AtomMsgSnd.mtext));
            Write(1, buff, 40, Alimentazione);
            if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
            {
                Write(1, "Cannot send message to new atom\n", 32, Alimentazione);
            }
            break;
        }
    }
}