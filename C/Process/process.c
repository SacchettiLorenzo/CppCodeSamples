#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILD 5

int main()
{
    pid_t my_pid, my_ppid, value;
    int exec = 0;

    int status;

    pid_t child_pid;

    for (int i = 0; i < NUM_CHILD; i++)
    {
        switch (value = fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            /* Perform actions specific to child */
            my_pid = getpid();   // get current process pid
            my_ppid = getppid(); // get parent pid
            printf("CHILD:  PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
            exit(EXIT_SUCCESS); // exit the process after the first execution, prevent the spawn of multiple useless process
            break;

        default:
            /* Perform actions specific to parent */
            my_pid = getpid();
            my_ppid = getppid();

            //prevent the parent to execute multiple times in the for loop
            if (exec == 0){
            printf("PARENT: PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
            exec = 1;
            }
            
            while ((child_pid = wait(&status)) != -1){
                //wait for all the child process to terminate and exit before termination of the parent
            }

            break;
        }
    }
    /* Both child and parent process will execute here!! */
    exit(EXIT_SUCCESS);
}
