#include "../include/attivatore.h"

struct sembuf sops;
int startSimulationSemId;
int shared_mem_id;
int sharedMemorySemId;
struct SharedMemory *SM;

int i;
int randomNumber;

struct itimerspec activationTimer;
timer_t activationtimer;
struct sigevent sigalarm;
char buff[60];
int masterPid;
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
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);
    srand(time(NULL));
    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

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

    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(sharedMemorySemId, &sops, 1);

    masterPid = SM->SMH.masterPid;

    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = 1;
    semop(sharedMemorySemId, &sops, 1);
    /*-------------------------------------------*/

    /*FIXME - THIS timer SHOULD START AFTER MASTER START SIMULATION*/
    /*SECTION - timer*/
    /*TODO - check if everything is necessary and change name*/
    /*sigalarm.sigev_notify = SIGEV_SIGNAL;*/
    sigalarm.sigev_signo = SIGUSR1;
    sigalarm.sigev_value.sival_ptr = &activationtimer;
    timer_create(CLOCK_REALTIME, &sigalarm, &activationtimer);
    activationTimer.it_value.tv_sec = 1;
    activationTimer.it_value.tv_nsec = 0;
    activationTimer.it_interval = activationTimer.it_value;
    timer_settime(activationtimer, 0, &activationTimer, NULL);
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    sops.sem_flg = 0;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Attivatore ready\n", 17, Attivatore);
}

void waitForParentStartSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Attivatore start simulation\n", 28, Attivatore);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Attivatore Handling SIGINT\n", 27, Attivatore);
        killpg(masterPid, SIGINT);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        choseAndSignal();
        break;

    default:
        break;
    }
}

void choseAndSignal()
{
    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(sharedMemorySemId, &sops, 1);
    SM->atomi = (struct Atomo *)((int *)SM + sizeof(struct SharedMemHeader));

    for (i = 0; i < ACTIVATION_PER_SECOND; i++)
    {
        randomNumber = (int)rand() % (SM->SMH.n_atomi);
        if ((SM->atomi + (randomNumber))->scoria != true)
        {
            if ((SM->atomi + (randomNumber))->pid != 0)
            {
                kill((SM->atomi + (randomNumber))->pid, SIGUSR1);
            }
        }
        else
        {
            i--;
        }
    }
    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = 1;
    semop(sharedMemorySemId, &sops, 1);
}
