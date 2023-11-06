#define _GNU_SOURCE 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILD 5

typedef enum {false,true}bool;

bool parentExecutedFuntion = false;

int busywork = 0;

struct sigaction sa;

int child_pid[CHILD];

int currently_forked = 0;

/* SIGUSR1 handler: used by child process */
void handle_signal(int signal) {
	
	printf("Child %d Handler\n",getpid());
}

/* SIGCHLD handler: used by parent process 
void handle_child(int signal) {
	
	while (wait(NULL) != -1 || errno != ECHILD);
	exit(0);
}*/

int main()
{
    pid_t my_pid, my_ppid, value;
    setvbuf(stdout, NULL, _IONBF, 0);

    /* Setting handler */
	bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	

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
            while (true)
            {
                busywork ++;
                busywork --;
            }
            
            exit(EXIT_SUCCESS);
            break;

        default:
            /* Perform actions specific to parent */
            if(!parentExecutedFuntion){
            my_pid = getpid();
            my_ppid = getppid();
            printf("PARENT: PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
            parentExecutedFuntion = !parentExecutedFuntion;
            }
            currently_forked++;

            int count = 0;
            if(currently_forked == CHILD-1)
            while (true)
            {
                if(count == CHILD)count = 0;
                count++;
                sleep(2);
                kill(child_pid[count],SIGUSR1);

            }
            
            
            break;
        }
    }

    /* Both child and parent process will execute here!! */
    exit(EXIT_SUCCESS);
}
