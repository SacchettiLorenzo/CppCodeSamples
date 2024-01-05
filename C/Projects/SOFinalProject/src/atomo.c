#include "../include/atomo.h"

/*SEMAPHORES*/
int startSimulationSemId;
int sharedMemorySemId;
struct sembuf sops;

/*QUEUES*/
int nAtom_Queue;
int splitting_Queue;
struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;
struct SplitMsgbuf SplitMsgSnd;
struct SplitMsgbuf SplitMsgRcv;

/*SHARED MEMEORY*/
int shared_mem_id;
struct SharedMemory *SM;

/*MISC*/
struct Atomo atomo;
int shared_mem_atom_position;
int masterPid;
int i;
char buff[40];
int masterPid;
int energy;
FILE *config;
int forkResult;
char *args_0[] = {"./atomo.out", "", (char *)0};

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        args_0[1] = argv[1];
    }
    init(argc, argv);
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

    srand(time(NULL));
    atomo.nAtom = 0;
    atomo.parentPid = getppid();
    atomo.inibito = 0;

    /*Start simulation SEM ----------------------*/
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600 | IPC_CREAT);
    if (startSimulationSemId == -1)
    {
        Write(1, "Cannot get simulation semaphore\n", 32, Atomo);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*Shared Memory -----------------------------*/
    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + NATOM_MAX * sizeof(struct Atomo), 0600 | IPC_CREAT);
    if (shared_mem_id == -1)
    {
        Write(1, "Cannot get shared memory segment\n", 33, Atomo);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    SM = shmat(shared_mem_id, NULL, 0);
    /*-------------------------------------------*/

    /*Shared Memory SEM -------------------------*/
    sharedMemorySemId = semget(SHARED_MEM_SEM_KEY, SHARED_MEM_NUM_RES, 0600 | IPC_CREAT);
    if (sharedMemorySemId == -1)
    {
        Write(1, "Cannot get shared memory semaphore\n", 35, Atomo);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    semctl(sharedMemorySemId, 0, SETVAL, 1);
    /*-------------------------------------------*/

    /*Signal Handler ----------------------------*/
    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_NOMASK;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    /*-------------------------------------------*/

    /*nAtom message queue*/
    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600);
    if (nAtom_Queue == -1)
    {
        Write(1, "Cannot get nAtom message queue\n", 31, Atomo);
        TEST_ERROR;
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*splitting request message queue*/
    splitting_Queue = msgget(SPLIT_REQUEST_KEY, 0600);
    if (splitting_Queue == -1)
    {
        Write(1, "Cannot get splitting message queue\n", 35, Atomo);
        TEST_ERROR
        exit(EXIT_FAILURE);
    }
    /*-------------------------------------------*/

    /*get nAtom from message queue. The sender is the parent*/
    if (msgrcv(nAtom_Queue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
        atomo.nAtom = atoi(AtomMsgRcv.mtext);
    }

    /*local and shared data update*/
    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(sharedMemorySemId, &sops, 1);

    shared_mem_atom_position = SM->SMH.n_atomi;
    SM->SMH.n_atomi = SM->SMH.n_atomi + 1;
    masterPid = SM->SMH.masterPid;
    setUpdateSharedMemory();

    sops.sem_num = ID_READ_WRITE;
    sops.sem_op = 1;
    semop(sharedMemorySemId, &sops, 1);

    ready();
}

void ready()
{
    if (shared_mem_atom_position <= N_ATOMI_INIT - 1)
    {
        sops.sem_num = ID_READY;
        sops.sem_op = 1;
        semop(startSimulationSemId, &sops, 1);
        Write(1, "Atomo ready\n", 12, Atomo);
    }
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
        /*Write(1, "Atomo Handling SIGUSR1\n", 23, Atomo);*/

        /*if possible split and generate new atom, if not become a scoria*/
        if (atomo.nAtom > MIN_N_ATOMICO)
        {
            if ((SM->atomi + (shared_mem_atom_position))->inibito == false)
            {
                split();
            }
        }
        else
        {
            if (atomo.scoria == false)
            {
                atomo.scoria = true;

                sops.sem_num = ID_READ_WRITE;
                sops.sem_op = -1;
                sops.sem_flg = 0;
                semop(sharedMemorySemId, &sops, 1);

                SM->atomi = (struct Atomo *)((int *)SM + sizeof(struct SharedMemHeader));
                (SM->atomi + (shared_mem_atom_position))->scoria = atomo.scoria;
                SM->SMH.scorie++;

                sops.sem_num = ID_READ_WRITE;
                sops.sem_op = 1;
                semop(sharedMemorySemId, &sops, 1);

                exit(EXIT_SUCCESS);
            }
        }
        break;
    default:
        break;
    }
}

void split()
{

    if ((int)rand() % 1000 > 1000 * ACTIVATION_PROBABILTY)
    {
        /*Write(1, "Not spliting\n", 22, Atomo);*/
        return;
    }
    /*
     */
    if (SM->SMH.inibitore == true)
    {
        SplitMsgSnd.mtype = 1;
        SplitMsgSnd.pid = getpid();
        SplitMsgSnd.nAtom = atomo.nAtom;
        SplitMsgSnd.split = false;
        if (msgsnd(splitting_Queue, &SplitMsgSnd, (int)(sizeof(struct SplitMsgbuf) - sizeof(long)), 0) == -1)
        {
            Write(1, "cannot send message to inibitore\n", 33, Atomo);
        }
        if (msgrcv(splitting_Queue, &SplitMsgRcv, sizeof(struct SplitMsgbuf) - sizeof(long), getpid(), 0) > 0)
        {
            if (SplitMsgRcv.split == false)
            {
                Write(1, "NO SPLIT\n", 9, Atomo);
                return;
            }
        }
    }
    /*
     * check in shared memory if inibitore is on DONE
     * if true send a request in message queue and wait for response DONE
     * in the request i should send the nAtom to let the inibitore absorb some energy
     * check the response and spit or not
     */

    switch (forkResult = fork())
    {
    case -1:
        Write(1, "Error splitting Atomo\n", 22, Atomo);
        TEST_ERROR;
        break;
    case 0:

        /*Write(1, "Splitting Atomo\n", 16, Atomo);*/
        if (execve(args_0[0], args_0, NULL) == -1)
        {
            Write(1, "Error splitting Atomo\n", 22, Atomo);
            Write(1, "meltdown\n", 9, Atomo);
            exit(EXIT_FAILURE);
        }
        break;

    default:
        /*REVIEW - (optional) create a more interesting nAtom division function*/
        AtomMsgSnd.mtype = forkResult;
        if (atomo.nAtom % 2 == 0)
        {
            snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", (atomo.nAtom / 2));
            atomo.nAtom = atomo.nAtom / 2;
            energy = calculateEnergy(atomo.nAtom, atomo.nAtom);
        }
        else
        {
            snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", (atomo.nAtom / 2));
            atomo.nAtom = (atomo.nAtom / 2) + 1;
            energy = calculateEnergy(atomo.nAtom, atomo.nAtom - 1);
        }

        if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
        {
            Write(1, "Error sending message\n", 22, Atomo);
            TEST_ERROR;
            exit(EXIT_FAILURE);
        }

        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = -1;
        sops.sem_flg = 0;
        semop(sharedMemorySemId, &sops, 1);

        SM->atomi = (struct Atomo *)((int *)SM + sizeof(struct SharedMemHeader));

        SM->SMH.ENERGIA_PRODOTTA += energy;
        SM->SMH.ATTIVAZIONI++;
        energy = 0;

        sops.sem_num = ID_READ_WRITE;
        sops.sem_op = 1;
        semop(sharedMemorySemId, &sops, 1);

        break;
    }
}

void setUpdateSharedMemory()
{
    SM->atomi = (struct Atomo *)((int *)SM + sizeof(struct SharedMemHeader));
    (SM->atomi + (shared_mem_atom_position))->pid = getpid();

    (SM->atomi + (shared_mem_atom_position))->parentPid = atomo.parentPid;
    (SM->atomi + (shared_mem_atom_position))->scoria = atomo.scoria;
    (SM->atomi + (shared_mem_atom_position))->inibito = atomo.inibito;
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

void getValueFromConfigFile(char *path)
{
    config = fopen(path, "r");
    while (fgets(buff, sizeof(buff), config))
    {
        sscanf(buff, "N_ATOMI_INIT %d", &N_ATOMI_INIT);
        sscanf(buff, "ACTIVATION_PROBABILTY %f", &ACTIVATION_PROBABILTY);
        sscanf(buff, "MIN_N_ATOMICO %d", &MIN_N_ATOMICO);
        sscanf(buff, "N_ATOM_MAX %d", &N_ATOM_MAX);
        sscanf(buff, "NATOM_MAX %d", &NATOM_MAX);
    }
    fclose(config);
}