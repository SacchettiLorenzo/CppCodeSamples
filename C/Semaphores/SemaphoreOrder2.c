#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define filename "file.txt"
#define NUM_CHILD 5
int order[NUM_CHILD] = {3, 4, 2, 5, 1};
// set the position of the process in the wanted order
// first generated process (i = 0) execute as third
// second generated process (i = 1)execute as fourth
// third generated process (i = 2)execute as second
// fourth generated process (i = 3)execute as fifth
// fifth generated process (i = 4)execute as first

int value;
int status;

FILE *fptr;
int s_id;

int main()
{
    s_id = semget(IPC_PRIVATE, NUM_CHILD, 0600);
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
            my_op.sem_num = i;
            my_op.sem_flg = 0;
            my_op.sem_op = -1*order[i];

            semop(s_id, &my_op, 1);
            fptr = fopen(filename, "a");
            fprintf(fptr, "process %d is on the file\n", i);
            fclose(fptr);
            for (size_t i = 0; i < NUM_CHILD; i++)
            {
                my_op.sem_num = i;
                my_op.sem_op = 1;
                semop(s_id, &my_op, 1);
            }

            exit(EXIT_SUCCESS);
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