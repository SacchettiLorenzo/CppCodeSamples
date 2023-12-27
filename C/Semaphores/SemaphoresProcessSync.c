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

#define ID_READY      0   /* figli pronti: padre puo` procedere */
#define ID_GO         1   /* padre pronto: figli possono procedere */

#define NUM_RISORSE 2 //(ID_READY, ID_GO)

#define NUM_PROC      10

struct sembuf sops;
int sem_id;
int status;
int main(){
    //get or create a new semaphore
sem_id = semget(IPC_PRIVATE, NUM_RISORSE, 0600);
//set the value of the semaphore to  0
semctl(sem_id, ID_READY, SETVAL, 0);
	semctl(sem_id, ID_GO, SETVAL, 0);
    /* Nessun flag per operazioni sui semafori */
	sops.sem_flg = 0;

    for (size_t i = 0; i < NUM_PROC; i++)
    {
        switch (fork()){
            case 0:
                /* 
			 * Informa il  padre che sono nato  e pronto a
			 * eseguire
			 */ 
            //tell the parent that the child is ready to execute
			sops.sem_num = ID_READY;
			sops.sem_op = 1;
			semop(sem_id, &sops, 1);
            write(1,"READY\n",6);
            
			//wait for the parent to tell when to start to execute
			sops.sem_num = ID_GO;
			sops.sem_op = -1;
			semop(sem_id, &sops, 1);
            write(1,"RUNNING\n",8);
            exit(EXIT_SUCCESS);
        }
    }

    //parent wait for all the child to become ready
    sops.sem_num = ID_READY;
	sops.sem_op = -NUM_PROC;
	semop(sem_id, &sops, 1);
    
    write(1,"ALL PROCESS READY\n,",18);
    
    //start the child 
	sops.sem_num = ID_GO;
	sops.sem_op = NUM_PROC;
	semop(sem_id, &sops, 1);
    

    while ((wait(&status)) != -1)
    {
        // wait for all the child process to terminate and exit before termination of the parent
    }
    
}

/*  at the beginning of the programm 10 child are created
*   the parent set sosp.sem_op to -NUM_PROC so that every child has to comuinicate that they are ready
*   the semop funtion add the value provided by sosp.sem_op to the current value of the semaphore
*   while the parent have a non 0 sosp.sem_op the process is waiting
*   each one of the chidl will set the ID_READY sosp.sem_op to -1
*   when the parent see ID_READY sosp.sem_op == 0 will continue the execution setting ID_GO sosp.sem_op to NUM_PROCC allowing the child process to execute
*
*   In this case only one semaphore set it is created
        ID_GO
        ID_READY
            are the identifier of the single semaphore inside the set
    
*/
