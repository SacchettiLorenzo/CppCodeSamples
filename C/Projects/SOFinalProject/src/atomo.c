#include "../include/atomo.h"
struct sembuf sops;
int startSimulationSemId;

struct Atomo atomo;

int masterPid = 0;
siginfo_t si;

struct AtomMsgbuf
{
    long mtype;
    char mtext[ATOM_MSG_LEN];
};
struct AtomMsgbuf AtomMsgSnd;
struct AtomMsgbuf AtomMsgRcv;

struct sigevent sigalarm;

int startSimulationSemId;
int nAtomQueue;
bool is_N_Atom = false;

int value;
char *args_0[] = {"./atomo.out", (char*)0};

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
    
    atomo.pid = getpid();
    atomo.nAtom = 0;
    atomo.masterPid = getppid();

    if (atomo.masterPid == 0)
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
    snprintf(AtomMsgSnd.mtext, ATOM_MSG_LEN, "%d", getpid());

    AtomMsgSnd.mtype = MASTER_QUE_TYPE;
    msgsnd(nAtomQueue, &AtomMsgSnd, ATOM_MSG_LEN, 0);

    
}

void ready()
{
    sops.sem_num = ID_READY;
    sops.sem_op = 1;
    semop(startSimulationSemId, &sops, 1);
    Write(1, "Atomo ready\n", 12, Atomo);
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
        Write(1, "Atomo Handling SIGINT\n", 22, Atomo);
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        if (is_N_Atom == false)
        {
            checkForMsg();
        }
        break;

    default:
        break;
    }
}

void checkForMsg()
{
    if (msgrcv(nAtomQueue, &AtomMsgRcv, ATOM_MSG_LEN, getpid(), 0) > 0)
    {
         atomo.nAtom = atoi(AtomMsgRcv.mtext);
        if ( atomo.nAtom > 0)
        {
            is_N_Atom = true;
            snprintf(writeBuffer, 25 + strlen(AtomMsgRcv.mtext) + 6, "Atomo: %d got nAtom %d\n", getpid(),  atomo.nAtom);
            Write(1, writeBuffer, 19 + strlen(AtomMsgRcv.mtext) + 6, Atomo);
            ready();
        }
    }
}
/*
void split(){
    switch (value = fork())
    {
    case -1:
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;
    case 0:
        if(execve(args_0[0], args_0, NULL) == -1){
                    Write(1,"Error splitting Atomo\n",22,Atomo);
                    TEST_ERROR;
                    exit(EXIT_FAILURE);
                }
            /*TODO: 
            l'atomo manda a master la richiesta di ottenere un nuovo nAtom
            se il pid del padre dell'atomo è già presente tra gli atomi usa il suo nAtom 
            per generare nAtom del nuovo atomo.
            Devo fare una differenza tra gli atomi creati dal nulla e qulli splittati

            Atomi creati dal nulla:
                operazione eseguita durante l'init del master e dal processo alimentazione
                viene generato un nAtom tra 0 e N_ATOM_MAX
            Atomi splittati:
                viene creato un nAtom tra 0 e il nAtom dell'atomo che viene splittato
                il master può trovare nAtom del padre quando riceve il suo pid sulla coda di messaggi
                il master esegue una ricerca lineare tra tutti gli atomi disponibili
                considerare le situazione in cui nAtom originale è pari o dispari per avere una suddivisione 
                di nAtom senza perdita dei decimali
            

        break;
    
    default:
        break;
    }
}

*/