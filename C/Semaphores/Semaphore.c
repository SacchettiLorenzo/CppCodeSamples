#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define SEM1 0
#define SEM2 1
#define NUM_RES 2

int semValue[NUM_RES];

int sem_id; // semaphore id

struct sembuf sops; //struct for semaphore operations

int main(){
    sem_id = semget(IPC_PRIVATE, NUM_RES, 0600);
    semctl(sem_id, SEM1, SETVAL, 0);
    semctl(sem_id, SEM2, SETVAL, 0);

    semValue[SEM1] = semctl(sem_id, SEM1, GETVAL);
    semValue[SEM2] = semctl(sem_id, SEM2, GETVAL);
    
    sops.sem_num = SEM1;    //setting semaphore 1
    sops.sem_op = -1;       //removing / taking resources / actual use of semaphore
    sops.flasg = 0;         //options
    semop(sem_id, &sops, 1); //sops could be an array of operations for different semaphores. in this case is only 1 semaphore and it is specified by the argument
    /*ACCESSING CRITICAL SECTION*/
        /*PERFORMING SOME ACTION*/
    /*LEAVING CRITICAL SECTION*/
    sops.sem_num = SEM1;    //setting semaphore 1
    sops.sem_op = -1;       //restore / return resources / actual use of semaphore
    sops.flasg = 0;         //options
    semop(sem_id, &sops, 1)

    sops.sem_num = SEM2;    //setting semaphore 2
    sops.sem_op = -1;       //removing / taking resources / actual use of semaphore
    sops.flasg = 0;         //options
    semop(sem_id, &sops, 1); //sops could be an array of operations for different semaphores. in this case is only 1 semaphore and it is specified by the argument
    /*ACCESSING CRITICAL SECTION*/
        /*PERFORMING SOME ACTION*/
    /*LEAVING CRITICAL SECTION*/
    sops.sem_num = SEM2;    //setting semaphore 2
    sops.sem_op = -1;       //restore / return resources / actual use of semaphore
    sops.flasg = 0;         //options
    semop(sem_id, &sops, 1)

} 

/* 
    semget: get the id of the semaphore specified by the key or by the IPC_PRIVATE
    IPC_PRIVATE: generate a totaly new semaphore set
    NUM_RES: number of sempahores inside a semaphore set
    semctl: semephore control operation
        SETVAL: set the value of the specified semaphore
        GETVAL: return the value of the specified semaphore
        GETPID: return the pid of the semaphore
        GETALL: return array with all the value of the semaphore. an address must be specified in the args
        SETALL: set all the semaphore value from an array
        GETZCTN: return number of process waiting for the specified semaphore to become 0
        GETNCNT: retunr number of process waiting for the specified semaphore to become greater than current value
    semop: perform an operation on the single semaphore in the semaphore set
        the second argument could rapresent a single sempaphore or an array of sempahore
        the number of semaphore to be considered in the operation is specified in the third paramenter



*/