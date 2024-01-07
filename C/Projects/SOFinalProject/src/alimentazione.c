#include "../include/alimentazione.h"

/*SEMAPHORES*/
int startSimulationSemId;
int sharedMemorySemId;
struct sembuf sops;

/*QUEUES*/
int nAtom_Queue;
struct AtomMsgbuf AtomMsgSnd;

/*SHARED MEMORY*/
int shared_mem_id;
struct SharedMemory *SM;

/*TIMERS*/
struct itimerspec atomGenerationTimer;
timer_t atomgenerationtimer;
struct sigevent sigusr;

/*MISC*/
int masterPid;
char *args_0[] = {"./atomo.out", "", (char *)0};
int i;
int forkResult;
char buff[40];
FILE *config;
FILE *tmp;
int tmpI;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        args_0[1] = argv[1];
    }
    init(argc, argv);
    ready();
    waitForParentStartSimulation();

    while (1)
    {
        pause();
    }
}

void init(int argc, char *argv[])
{
    if (argc > 1)
    {
        getValueFromConfigFile(argv[1]);
    }
    /*nAtom message queue*/
    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600 | IPC_CREAT);
    if (nAtom_Queue == -1)
    {
        Write(2, "Cannot get nAtom message queue\n", 31, Alimentazione);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*Start simulation SEM ----------------------*/
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);
    if (startSimulationSemId == -1)
    {
        Write(2, "Cannot get simulation semaphore\n", 32, Alimentazione);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }

    /*Shared Memory SEM -------------------------*/
    sharedMemorySemId = semget(SHARED_MEM_SEM_KEY, SHARED_MEM_NUM_RES, 0600 | IPC_CREAT);
    if (sharedMemorySemId == -1)
    {
        Write(2, "Cannot get shared memory semaphore\n", 35, Alimentazione);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*Shared Memory -----------------------------*/
    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + NATOM_MAX * sizeof(struct SharedAtomo), 0600 | IPC_CREAT);
    if (shared_mem_id == -1)
    {
        Write(2, "Cannot get shared memory segment\n", 33, Alimentazione);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    SM = shmat(shared_mem_id, NULL, 0);

    masterPid = SM->SMH.masterPid;
    /*-------------------------------------------*/

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    sigusr.sigev_signo = SIGUSR1;
    sigusr.sigev_value.sival_ptr = &atomgenerationtimer;
    timer_create(CLOCK_REALTIME, &sigusr, &atomgenerationtimer);
    atomGenerationTimer.it_value.tv_sec = STEP;
    atomGenerationTimer.it_value.tv_nsec = 0;
    atomGenerationTimer.it_interval = atomGenerationTimer.it_value;
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
    timer_settime(atomgenerationtimer, 0, &atomGenerationTimer, NULL);
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
        /*Write(1, "Alimentazione generate new atoms\n", 33, Alimentazione);*/
        if (SM->SMH.n_atomi + N_NUOVI_ATOMI < NATOM_MAX)
        {
            generateNewAtoms();
        }
        break;

    default:
        break;
    }
}

void generateNewAtoms()
{
    for (i = 0; i < N_NUOVI_ATOMI; i++)
    {
        switch (forkResult = fork())
        {
        case -1:
            Write(2, "Error forking\n", 14, Alimentazione);
            break;

        case 0:
            Write(2, "calling Atomo\n", 14, Alimentazione);
            if (execve(args_0[0], args_0, NULL) == -1)
            {
                Write(2, "Error calling Atomo\n", 20, Alimentazione);
                Write(1, "meltdown\n", 9, Alimentazione);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
            break;
        default:
            AtomMsgSnd.mtype = forkResult;
            snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator(N_ATOM_MAX));
            bzero(buff, 40);
            snprintf(buff, 40, "alim create atom %d with %d\n", forkResult, atoi(AtomMsgSnd.mtext));
            Write(1, buff, 40, Alimentazione);
            if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
            {
                Write(2, "Cannot send message to new atom\n", 32, Alimentazione);
            }
            break;
        }
    }
}

void getValueFromConfigFile(char *path)
{
    config = fopen(path, "r");
    if (config == NULL)
    {
        Write(2, "Unable to open config file\n", 27, Master);
        exit(EXIT_FAILURE);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "STEP %d", &STEP);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "N_NUOVI_ATOMI %d", &N_NUOVI_ATOMI);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "N_ATOM_MAX %d", &N_ATOM_MAX);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "NATOM_MAX %d", &NATOM_MAX);
    }
    fclose(config);

    tmp = fopen("../tmp/limits.txt", "r");
    if (tmp == NULL)
    {
        Write(2, "Unable to open limits file\n", 25, Alimentazione);
        TEST_ERROR;
    }
    else
    {
        while (fgets(buff, sizeof(buff), tmp))
        {
            sscanf(buff, "process %d", &tmpI);
            if(tmpI >NATOM_MAX)NATOM_MAX = tmpI;
        }
    }
}