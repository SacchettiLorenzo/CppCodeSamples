#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define CHILD 5

typedef enum
{
    false,
    true
} bool;

bool parentExecutedFuntion = false;

int busywork = 0;

struct sigaction sa_1;
struct sigaction sa_2;

pid_t child_pid[CHILD];

int currently_forked = 0;

/* SIGUSR1 handler: used by child process */
void handle_signal_from_parent_to_child(int signal)
{

    // printf("Child %d Handler\n",getpid());
    write(1, "Child handler\n", 14);
}

int main()
{
    pid_t my_pid, my_ppid, value;
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Setting handler for child process*/
    bzero(&sa_1, sizeof(sa_1));
    sa_1.sa_handler = handle_signal_from_parent_to_child;
    sigaction(SIGUSR1, &sa_1, NULL);

    for (size_t i = 0; i < CHILD; i++)
    {
        switch (value = fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            /* Perform actions specific to child */
            my_pid = getpid();
            child_pid[i] = my_pid;
            my_ppid = getppid();
            printf("CHILD:  PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
            //doing work on child
            
            sigset_t sigset;
            sigemptyset(&sigset);
            sigaddset(&sigset, SIGUSR1);
            int sig;
            int result = sigwait(&sigset, &sig); 
            
            exit(EXIT_SUCCESS);
            break;

        default:
            /* Perform actions specific to parent */
            if (!parentExecutedFuntion)
            {
                my_pid = getpid();
                my_ppid = getppid();
                printf("PARENT: PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
                parentExecutedFuntion = !parentExecutedFuntion;
            }
            currently_forked++;

            if(currently_forked == CHILD-1){
                sleep(5);
            kill(child_pid[0],SIGUSR1);
            kill(child_pid[1],SIGUSR1);
            kill(child_pid[2],SIGUSR1);
            kill(child_pid[3],SIGUSR1);
            kill(child_pid[4],SIGUSR1);

            }
                
            

            break;
        }
    }

    /* Both child and parent process will execute here!! */
    exit(EXIT_SUCCESS);
}
