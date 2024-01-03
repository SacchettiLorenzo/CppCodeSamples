#include "../include/inibitore.h"

/*SEMAPHORES*/
int startSimulationSemId;
int sharedMemorySemId;
struct sembuf sops;

/*QUEUES*/
int splitting_Queue;
struct SplitMsgbuf SplitMsgRcv;
struct SplitMsgbuf SplitMsgSnd;

/*SHARED MEMORY*/
int shared_mem_id;
struct SharedMemory *SM;

/*MISC*/
int masterPid;
char buff[40];
FILE *config;
int energy;
char bufff[100];

/*TIMERS*/
struct itimerspec recurrentWorkTimerSpec;
timer_t recurrentWork_timer;
struct sigevent sigUsr1;

int main(int argc, char *argv[])
{
    init(argc, argv);
    ready();
    waitForParentStartSimulation();

    /*TODO - select ATOM_INIBITION_NUMBER atoms and cgange the value in the shared memory*/

    while (1)
    {
        while (msgrcv(splitting_Queue, &SplitMsgRcv, sizeof(struct SplitMsgbuf) - sizeof(long), 0, 0) > 0)
        {
            SplitMsgRcv.nAtom = SplitMsgRcv.nAtom / 2;
            if (SplitMsgRcv.nAtom % 2 == 0)
            {
                energy = calculateEnergy(SplitMsgRcv.nAtom, SplitMsgRcv.nAtom);
            }
            else
            {
                energy = calculateEnergy(SplitMsgRcv.nAtom, SplitMsgRcv.nAtom - 1);
            }

            if (SM->SMH.ENERGIA_PRODOTTA - SM->SMH.ENERGIA_CONSUMATA - SM->SMH.ENERGIA_ASSORBITA + energy > ENERGY_EXPLODE_THRESHOLD)
            {
                SplitMsgSnd.split = false;
            }
            else
            {
                SplitMsgSnd.split = true;
            }
            if (SplitMsgRcv.pid == 0)
            {
                continue;
            }
            else
            {
                SplitMsgSnd.mtype = SplitMsgRcv.pid;
            }
            if (msgsnd(splitting_Queue, &SplitMsgSnd, (int)(sizeof(struct SplitMsgbuf) - sizeof(long)), 0) == -1)
            {
                Write(1, "cannot send message to atomo\n", 29, Inibitore);
                bzero(bufff, 100);
                snprintf(bufff, 100, "mtype:%ld, split: %d\n", SplitMsgSnd.mtype, (int)SplitMsgSnd.split);
                Write(1, bufff, 100, Inibitore);
                
            }
        }

        /*pause();*/
    }
}

void init(int argc, char *argv[])
{
    if (argc > 1)
    {
        getValueFromConfigFile(argv[1]);
    }
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600);

    /*splitting request message queue*/
    splitting_Queue = msgget(SPLIT_REQUEST_KEY, 0600);
    SplitMsgSnd.pid = 0;
    /*-------------------------------------------*/

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
    sigaction(SIGUSR1, &sa, NULL);

    sigUsr1.sigev_signo = SIGUSR1;
    sigUsr1.sigev_value.sival_ptr = &recurrentWork_timer;
    timer_create(CLOCK_REALTIME, &sigUsr1, &recurrentWork_timer);
    recurrentWorkTimerSpec.it_value.tv_sec = 1;
    recurrentWorkTimerSpec.it_value.tv_nsec = 0;
    recurrentWorkTimerSpec.it_interval = recurrentWorkTimerSpec.it_value;
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
    timer_settime(recurrentWork_timer, 0, &recurrentWorkTimerSpec, NULL);
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:
        Write(1, "Inibitore Handling SIGINT\n", 27, Inibitore);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        semop(sharedMemorySemId, &sops, 1);

        SM->SMH.ENERGIA_ASSORBITA = +ENERGY_ABSORPTION;

        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = 1;
        semop(sharedMemorySemId, &sops, 1);
        break;
    default:
        break;
    }
}

void getValueFromConfigFile(char *path)
{
    config = fopen(path, "r");
    if (config == NULL)
    {
        Write(1, "Unable to open config file\n", 27, Master);
        exit(EXIT_FAILURE);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "N_ATOM_MAX %d", &N_ATOM_MAX);
        sscanf(buff, "ENERGY_EXPLODE_THRESHOLD %d", &ENERGY_EXPLODE_THRESHOLD);
        sscanf(buff, "ENERGY_ABSORPTION %d", &ENERGY_ABSORPTION);
    }
    fclose(config);
}

int calculateEnergy(int nAtom1, int nAtom2)
{
    if (nAtom1 > nAtom2)
    {
        return nAtom1 * nAtom2 - nAtom1;
    }
    else
    {
        return nAtom1 * nAtom2 - nAtom2;
    }
}