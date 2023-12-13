#include "../include/atomo.h"
struct sembuf sops;
int startSimulationSemId;

struct Atomo atomo;

siginfo_t si;

struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;

struct sigevent sigalarm;

int startSimulationSemId;
int sharedMemorySemId;
int nAtom_Queue;

int value;
char *args_0[] = {"./atomo.out", (char *)0};

int shared_mem_id;
int shared_mem_atom_position;
struct SharedMemory *SM;

int atomPositionInSharedMem;

int i;
char buff[40];

int main(int argc, char *argv[])
{
    init();

    waitForMasterStartSimulation();

    pause();
    Write(1, "Atomo terminating\n", 18, Atomo);
}

void init()
{
    atomo.nAtom = 0;
    atomo.parentPid = getppid();
    atomo.inibito = 0;
    startSimulationSemId = semget(START_SIMULATION_SEM_KEY, START_SIMULATION_NUM_RES, 0600 | IPC_CREAT);

    shared_mem_id = shmget(SHARED_MEM_KEY, sizeof(struct SharedMemHeader) + N_ATOMI_INIT * sizeof(struct Atomo), 0600 | IPC_CREAT);
    if (shared_mem_id == -1)
    {
        Write(1, "Error shmget\n", 12, Master);
        TEST_ERROR;
    }

    sharedMemorySemId = semget(START_SIMULATION_SEM_KEY, 2, 0600 | IPC_CREAT);
    semctl(sharedMemorySemId, 0, SETVAL, 1);

    bzero(&sa, sizeof(sa));
    sa.sa_sigaction = handle_signals;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    nAtom_Queue = msgget(N_ATOM_QUEUE_KEY, 0600);

    if (msgrcv(nAtom_Queue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
        atomo.nAtom = atoi(AtomMsgRcv.mtext);
        if (atomo.nAtom > 0)
        {
            snprintf(writeBuffer, 25 + strlen(AtomMsgRcv.mtext) + 6, "Atomo: %d got nAtom %d\n", getpid(), atomo.nAtom);
            Write(1, writeBuffer, 19 + strlen(AtomMsgRcv.mtext) + 6, Atomo);
        }
    }
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = 0;
    semop(sharedMemorySemId, &sops, 1);
    SM = shmat(shared_mem_id, NULL, 0);
    shared_mem_atom_position = SM->SMH.n_atomi;
    SM->SMH.n_atomi = SM->SMH.n_atomi + 1;
    setUpdateSharedMemory();
    shmdt(SM);
    sops.sem_num = 0;
    sops.sem_op = 1;
    semop(sharedMemorySemId, &sops, 1);

    ready();
}

void ready()
{
    /*FIXME -
    if splitted atom this operation is useless
    */
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Atomo ready\n", 12, Atomo);
}

void waitForMasterStartSimulation()
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
        Write(1, "Atomo Handling SIGUSR1\n", 23, Atomo);
        split();
        break;
    default:
        pause();
        break;
    }
}

void split()
{
    switch (value = fork())
    {
    case -1:
        Write(1, "Error splitting Atomo\n", 22, Atomo);
        TEST_ERROR;
        break;
    case 0:

        if (execve(args_0[0], args_0, NULL) == -1)
        {
            Write(1, "Error splitting Atomo\n", 22, Atomo);
            TEST_ERROR;
            exit(EXIT_FAILURE);
        }

        break;

    default:
        AtomMsgSnd.mtype = value;
        snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", normalDistributionNumberGenerator(0));
        if (msgsnd(nAtom_Queue, &AtomMsgSnd, ATOM_MSG_LEN, 0) == -1)
        {
            Write(1, "Error sending message\n", 22, Atomo);
            TEST_ERROR;
        }
        break;
    }
}

void setUpdateSharedMemory()
{
    SM->atomi = (struct Atomo *)((int *)SM + sizeof(struct SharedMemHeader));
    (SM->atomi + (shared_mem_atom_position))->pid = getpid();
    (SM->atomi + (shared_mem_atom_position))->nAtom = atomo.nAtom;
    (SM->atomi + (shared_mem_atom_position))->parentPid = atomo.parentPid;
    (SM->atomi + (shared_mem_atom_position))->scoria = atomo.scoria;
    (SM->atomi + (shared_mem_atom_position))->inibito = atomo.inibito;
}