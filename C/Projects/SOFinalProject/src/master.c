#include "../include/master.h"
#include <fcntl.h>

/*TODO - send id of semaphores - message queues - shared memory to child using pipes*/
/*TODO - change write output 1 -> 2 where handling errors*/
/*SEMAPHORES*/
int startSimulationSemId;
int sharedMemorySemId;
struct sembuf sops;

/*QUEUES*/
int nAtom_Queue;
int splitting_Queue;
struct AtomMsgbuf AtomMsgRcv;
struct AtomMsgbuf AtomMsgSnd;

/*SHARED MEMORY*/
int shared_mem_id;
struct SharedMemory *SM;
struct SharedMemHeader SMHBuffer;

/*TIMERS*/
struct itimerspec recurrentWorkTimerSpec;
timer_t recurrentWork_timer;
struct sigevent sigUsr1;

struct itimerspec timeoutTimerSpec;
timer_t timeout_timer;
struct sigevent sigInt;

/*MISC*/
int forkResult;
int status;
struct ServiceProcessData service_process[N_SERVICE_PROCESS];
pid_t childPid;
int i, j;
int totalChild;
char *DEFAULT_CONFIG_FILE = "../config/config_0.txt";
char *args_0[] = {"./attivatore.out", "", (char *)0};
char *args_1[] = {"./alimentazione.out", "", (char *)0};
char *args_2[] = {"./inibitore.out", "", (char *)0};
char *args_3[] = {"./atomo.out", "", (char *)0};
int current_atom_quantity;
char buff[256];
bool simulation = false;
FILE *config;
FILE *memoryDump;
FILE *tmp;
int tmpI;

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        args_0[1] = argv[1];
        args_1[1] = argv[1];
        args_2[1] = argv[1];
        args_3[1] = argv[1];
    }
    else
    {
        args_0[1] = DEFAULT_CONFIG_FILE;
        args_1[1] = DEFAULT_CONFIG_FILE;
        args_2[1] = DEFAULT_CONFIG_FILE;
        args_3[1] = DEFAULT_CONFIG_FILE;
    }

    init(argc, argv);

    for (i = 0; i < totalChild; i++)
    {
        switch (forkResult = fork())
        {
        case -1:
            Write(1, "Error on fork\n", 14, Master);
            TEST_ERROR;
            break;

        case 0:
            if (i == 0)
            {
                Write(1, "calling Attivatore\n", 19, Master);
                if (execve(args_0[0], args_0, NULL) == -1)
                {
                    Write(2, "Error calling Attivatore\n", 25, Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i == 1)
            {
                Write(1, "calling Alimentazione\n", 22, Master);
                if (execve(args_1[0], args_1, NULL) == -1)
                {
                    Write(2, "Error calling Alimentazione\n", 28, Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i == 2)
            {
                Write(1, "calling Inibitore\n", 18, Master);
                sops.sem_num = ID_READ_WRITE;
                sops.sem_op = -1;
                sops.sem_flg = 0;
                semop(sharedMemorySemId, &sops, 1);

                SM->SMH.inibitorePid = getpid();

                sops.sem_num = ID_READ_WRITE;
                sops.sem_op = 1;
                semop(sharedMemorySemId, &sops, 1);

                if (execve(args_2[0], args_2, NULL) == -1)
                {
                    Write(2, "Error calling Inibitore\n", 24, Master);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
                exit(EXIT_SUCCESS);
                break;
            }
            if (i > 2)
            {
                Write(1, "calling Atomo\n", 14, Master);
                if (execve(args_3[0], args_3, NULL) == -1)
                {
                    Write(2, "Error calling Atomo\n", 20, Master);
                    Write(1, "meltdown\n", 9, Master);
                    /*TEST_ERROR;*/
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
                (service_process + i)->pid = forkResult;
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
            }

            if (i >= N_SERVICE_PROCESS)
            {
                AtomMsgSnd.mtype = forkResult;
                snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator(N_ATOM_MAX));
                if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
                {
                    Write(1, "Cannot sent nAtom\n", 18, Master);
                }
            }
            break;
        }
    }

    waitForChildReady();

    waitpid((service_process + 0)->pid, &status, 0);
    waitpid((service_process + 1)->pid, &status, 0);
    waitpid((service_process + 2)->pid, &status, 0);

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
    else
    {
        getValueFromConfigFile(DEFAULT_CONFIG_FILE);
    }

    totalChild = N_ATOMI_INIT + N_SERVICE_PROCESS;

    srand(time(NULL));
    bzero(&SMHBuffer, sizeof(struct SharedMemHeader));

    /*Signal Handler ----------------------------*/
    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals; /*same as handler*/
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    /*-------------------------------------------*/

    /*Start simulation SEM ----------------------*/
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600 | IPC_CREAT);
    if (startSimulationSemId == -1)
    {
        Write(2, "Cannot get simulation semaphore\n", 32, Master);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }

    semctl(startSimulationSemId, ID_READY, SETVAL, 0);
    semctl(startSimulationSemId, ID_GO, SETVAL, 0);
    /*-------------------------------------------*/

    /*Shared Memory SEM -------------------------*/
    sharedMemorySemId = semget(SHARED_MEM_SEM_KEY, SHARED_MEM_NUM_RES, 0600 | IPC_CREAT);
    if (sharedMemorySemId == -1)
    {
        Write(2, "Cannot get shared memory semaphore\n", 35, Master);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    semctl(sharedMemorySemId, 0, SETVAL, 1);
    /*-------------------------------------------*/

    /*nAtom message queue*/
    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600 | IPC_CREAT);
    if (nAtom_Queue == -1)
    {
        Write(2, "Cannot get nAtom message queue\n", 31, Master);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/
    /*splitting request message queue*/
    splitting_Queue = msgget(SPLIT_REQUEST_KEY, 0600 | IPC_CREAT);
    if (splitting_Queue == -1)
    {
        Write(2, "Cannot get splitting message queue\n", 35, Master);
        TEST_ERROR
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*Shared Memory -----------------------------*/
    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + NATOM_MAX * sizeof(struct SharedAtomo), 0600 | IPC_CREAT);
    if (shared_mem_id == -1)
    {
        Write(2, "Cannot get shared memory segment\n", 33, Master);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    SM = shmat(shared_mem_id, NULL, 0);

    SM->SMH.n_atomi = 0;
    SM->SMH.masterPid = getpid();
    SM->atomi = (struct SharedAtomo *)((int *)SM + sizeof(struct SharedMemHeader));
    SM->SMH.simulation = false;
    SM->SMH.inibitore = false;
    SM->SMH.ATTIVAZIONI = 0;
    SM->SMH.ENERGIA_ASSORBITA = 0;
    SM->SMH.ENERGIA_CONSUMATA = 0;
    SM->SMH.ENERGIA_PRODOTTA = 0;
    SM->SMH.inibitore = (bool)inibitore;
    SM->SMH.scorie = 0;
    /*-------------------------------------------*/

    /*Timer--------------------------------------*/
    sigUsr1.sigev_signo = SIGUSR1;
    sigUsr1.sigev_value.sival_ptr = &recurrentWork_timer;
    timer_create(CLOCK_REALTIME, &sigUsr1, &recurrentWork_timer);
    recurrentWorkTimerSpec.it_value.tv_sec = 1;
    recurrentWorkTimerSpec.it_value.tv_nsec = 0;
    recurrentWorkTimerSpec.it_interval = recurrentWorkTimerSpec.it_value;

    sigInt.sigev_signo = SIGINT;
    sigInt.sigev_value.sival_ptr = &timeout_timer;
    timer_create(CLOCK_REALTIME, &sigInt, &timeout_timer);
    timeoutTimerSpec.it_value.tv_sec = SIM_DURATION;
    timeoutTimerSpec.it_value.tv_nsec = 0;
    timeoutTimerSpec.it_interval = timeoutTimerSpec.it_value;

    /*-------------------------------------------*/
}

void waitForChildReady()
{
    sops.sem_num = ID_READY;
    sops.sem_op = -totalChild;
    sops.sem_flg = 0;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "All process ready: starting simulation\n", 39, Master);
    startSimulation();
}

void startSimulation()
{
    sops.sem_num = ID_GO;
    sops.sem_op = N_SERVICE_PROCESS;
    semop(startSimulationSemId, &sops, 1);
    timer_settime(recurrentWork_timer, 0, &recurrentWorkTimerSpec, NULL);
    timer_settime(timeout_timer, 0, &timeoutTimerSpec, NULL);
    simulation = true;
}

void handle_signals(int signal, siginfo_t *info, void *v)
{
    switch (signal)
    {
    case SIGINT:

        if (info->si_pid != getpid() && info->si_pid != 1)
        {
            Write(1, "Process terminated by the user\n", 31, Master);
            /*printf("%d", info->si_pid);*/
        }
        else
        {
            if (simulation)
            {
                Write(1, "timeout\n", 8, Master);
            }
        }
        stopSimulation();

        break;
    case SIGUSR1:
        if (simulation)
        {
            sops.sem_num = ID_READ_WRITE;
            sops.sem_op = -1;
            sops.sem_flg = 0;
            if (semop(sharedMemorySemId, &sops, 1) == -1)
            {
                Write(2, "Error on SEM Master (1)\n", 24, Master);
            }

            if (SM->SMH.ENERGIA_PRODOTTA - SM->SMH.ENERGIA_CONSUMATA - SM->SMH.ENERGIA_ASSORBITA > ENERGY_EXPLODE_THRESHOLD)
            {
                Write(1, "explode\n", 8, Master);
                stopSimulation();
            }

            if (SM->SMH.ENERGIA_PRODOTTA < SM->SMH.ENERGIA_CONSUMATA + SM->SMH.ENERGIA_ASSORBITA)
            {
                Write(1, "blackout (1)\n", 8, Master);
                stopSimulation();
            }

            if(SM->SMH.n_atomi == SM->SMH.scorie){
                Write(1, "blackout  (2)\n", 8, Master);
                stopSimulation();
            }

            SM->SMH.ENERGIA_CONSUMATA += ENERGY_DEMAND;
            bzero(buff, 256);
            snprintf(buff, 256, "[Total] ATOMI: %d |SCORIE: %d |SCISSIONI: %d |ENERGIA PRODOTTA: %d |ENERGIA CONSUMATA: %d |ENERGIA ASSORBITA: %d\n",
                     SM->SMH.n_atomi, SM->SMH.scorie, SM->SMH.ATTIVAZIONI, SM->SMH.ENERGIA_PRODOTTA, SM->SMH.ENERGIA_CONSUMATA, SM->SMH.ENERGIA_ASSORBITA);
            Write(1, buff, 256, Master);

            bzero(buff, 256);
            snprintf(buff, 256, "[Partial] NUOVO ATOMI: %d |NUOVE SCORIE: %d |SCISSIONI: %d |ENERGIA PRODOTTA:%d |ENERGIA CONSUMATA: %d |ENERGIA ASSORBITA: %d\n",
                     SM->SMH.n_atomi - SMHBuffer.n_atomi, SM->SMH.scorie - SMHBuffer.scorie, SM->SMH.ATTIVAZIONI - SMHBuffer.ATTIVAZIONI, SM->SMH.ENERGIA_PRODOTTA - SMHBuffer.ENERGIA_PRODOTTA, SM->SMH.ENERGIA_CONSUMATA - SMHBuffer.ENERGIA_CONSUMATA, SM->SMH.ENERGIA_ASSORBITA - SMHBuffer.ENERGIA_ASSORBITA);
            Write(1, buff, 256, Master);

            memcpy(&SMHBuffer, &SM->SMH, sizeof(struct SharedMemHeader));

            sops.sem_num = ID_READ_WRITE;
            sops.sem_op = 1;
            if (semop(sharedMemorySemId, &sops, 1) == -1)
            {
                Write(2, "Error on SEM Master (2)\n", 24, Master);
            }
        }
        break;
    default:
        break;
    }
}

void stopSimulation()
{

    simulation = false;
    killpg(getpid(), SIGINT);
    
    /*sops.sem_num = ID_READ_WRITE;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    if (semop(sharedMemorySemId, &sops, 1) == -1)
    {
        Write(2, "Error on SEM Master (3)\n", 24, Master);
    }
    */
    

    SM->atomi = (struct SharedAtomo *)((int *)SM + sizeof(struct SharedMemHeader));
    for (i = 0; i < SM->SMH.n_atomi; i++)
    {
        waitpid((SM->atomi + i)->pid, &status, 0);
    }

    dumpMemory();

    /*
    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = 1;
    if (semop(sharedMemorySemId, &sops, 1) == -1)
    {
        Write(2, "Error on SEM Master (4)\n", 24, Master);
    }
    */

    msgctl(nAtom_Queue, IPC_RMID, NULL);
    msgctl(splitting_Queue, IPC_RMID, NULL);
    semctl(startSimulationSemId, 0, IPC_RMID);
    semctl(sharedMemorySemId, 0, IPC_RMID);
    shmdt(SM);
    shmctl(shared_mem_id, IPC_RMID, NULL);

    exit(EXIT_SUCCESS);
}

void  dumpMemory()
{
    memoryDump = fopen("../output/memorydump.log", "w");
    if (memoryDump == NULL)
    {
        Write(2, "Error opening memory dump file\n", 31, Master);
    }

    fprintf(memoryDump, "-Total- ATOMI: %d SCORIE: %d SCISSIONI: %d ENERGIA PRODOTTA:%d ENERGIA CONSUMATA: %d ENERGIA ASSORBITA: %d\n\n",
            SM->SMH.n_atomi, SM->SMH.scorie, SM->SMH.ATTIVAZIONI, SM->SMH.ENERGIA_PRODOTTA, SM->SMH.ENERGIA_CONSUMATA, SM->SMH.ENERGIA_ASSORBITA);

    for (i = 0; i < SM->SMH.n_atomi; i++)
    {
        fprintf(memoryDump, "pid: %d, parent pid: %d, scoria: %d, inibito: %d\n", (SM->atomi + i)->pid, (SM->atomi + i)->parentPid, (SM->atomi + i)->scoria, (SM->atomi + i)->inibito);
    }

    fclose(memoryDump);
}

void getValueFromConfigFile(char *path)
{
    config = fopen(path, "r");
    if (config == NULL)
    {
        Write(2, "Unable to open config file\n", 27, Master);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "N_ATOMI_INIT %d", &N_ATOMI_INIT);
        sscanf(buff, "ENERGY_DEMAND %d", &ENERGY_DEMAND);
        sscanf(buff, "SIM_DURATION %d", &SIM_DURATION);
        sscanf(buff, "ENERGY_EXPLODE_THRESHOLD %d", &ENERGY_EXPLODE_THRESHOLD);
        sscanf(buff, "N_ATOM_MAX %d", &N_ATOM_MAX);
        sscanf(buff, "NATOM_MAX %d", &NATOM_MAX);
        sscanf(buff, "INIBITORE %d", &inibitore);
    }

    fclose(config);

    system("ulimit -a > ../tmp/limits.txt");
    tmp = fopen("../tmp/limits.txt", "r");
    if (tmp == NULL)
    {
        Write(1, "Unable to open limits file\n", 25, Master);
        TEST_ERROR;
    }
    else
    {
        while (fgets(buff, sizeof(buff), tmp))
        {
            sscanf(buff, "process %d", &tmpI);
            if (tmpI > NATOM_MAX)
                NATOM_MAX = tmpI;
        }
    }
}
