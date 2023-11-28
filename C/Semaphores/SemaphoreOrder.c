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

#define filename "file.txt"
#define NUM_CHILD 5

#define TEST_ERROR if (errno) {fprintf(stderr,				\
				       "%s:%d: PID=%5d: Error %d (%s)\n", \
				       __FILE__,			\
				       __LINE__,			\
				       getpid(),			\
				       errno,				\
				       strerror(errno));}

typedef enum
{
    false,
    true
} bool;
FILE *fptr;
int s_id;
int m_id;
int order[NUM_CHILD] = {3, 4, 2, 5, 1};
//set the position of the process in the wanted order
//first generated process (i = 0) execute as third
//second generated process (i = 1)execute as fourth
//third generated process (i = 2)execute as second
//fourth generated process (i = 3)execute as fifth
//fifth generated process (i = 4)execute as first

int value;
int status;

//shared data structure
struct shared
{
    int current;
};

int main()
{
    struct shared *sh;
    //get semaphore
    s_id = semget(IPC_PRIVATE, NUM_CHILD, 0600);
    //get shared data structure
    m_id = shmget(IPC_PRIVATE, NUM_CHILD * sizeof(struct shared), 0600);
    sh = shmat(m_id, NULL, 0);
    sh->current = 1;
    
    for (size_t i = 0; i < NUM_CHILD; i++)
    {
        semctl(s_id, i, SETVAL, 1);
    }

    for (int i = 0; i < NUM_CHILD; i++)
    {
        switch (value = fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            struct sembuf my_op;
            int place = order[i];
            while (1)
            {
                my_op.sem_num = NUM_CHILD;
                my_op.sem_flg = 0;
                my_op.sem_op = -1;
                if (sh->current == place)
                {
                    semop(s_id, &my_op, 1); /* blocking if others hold resource */
                    /* NOW IN CRITICAL SECTION */
                    fptr = fopen(filename, "a");
                    fprintf(fptr, "process %d is on the file\n", i);
                    fclose(fptr);
                    sh->current++;
                    my_op.sem_op = 1; /* releasing the resource */
                    semop(s_id, &my_op, 1);
                    break;
                }
                else
                {
                   continue;
                }
            }
            exit(EXIT_SUCCESS); // exit the process after the first execution, prevent the spawn of multiple useless process
            break;

        default:

            break;
        }
    }

    while ((wait(&status)) != -1)
    {
        // wait for all the child process to terminate and exit before termination of the parent
    }
    fptr = fopen(filename, "a");
    fprintf(fptr, "\n");
    fclose(fptr);
}