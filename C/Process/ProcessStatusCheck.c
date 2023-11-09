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

    pid_t child_pid;
    int status;

    for (int i = 0; i < NUM_CHILD; i++)
    {
        switch (value = fork())
        {
        case -1:

            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:

            my_pid = getpid();
            my_ppid = getppid();
            printf("CHILD:  PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
            exit(EXIT_SUCCESS);
            break;

        default:

            my_pid = getpid();
            my_ppid = getppid();

            if (exec == 0)
            {
                printf("PARENT: PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
                exec = 1;
            }

            // wait for the process and print the analysis of the status
            while ((child_pid = wait(&status)) != -1)
            {

                if (WIFEXITED(status))
                {
                    printf("  child correctly exited with status %d\n", WEXITSTATUS(status));
                }
                if (WIFSIGNALED(status))
                {
                    printf("  child terminated by the signal %d\n", WTERMSIG(status));
                    if (WCOREDUMP(status))
                    {
                        printf("  child produced a core dump\n");
                    }
                }

                if (WIFSTOPPED(status))
                {
                    printf("  child stopped by signal %d\n", WSTOPSIG(status));
                }

                if (WIFCONTINUED(status))
                {
                    printf("  child stopped by signal %d\n", WSTOPSIG(status));
                }
            }

            break;
        }
    }
        exit(EXIT_SUCCESS);
}

/*
WIFSIGNALED(status) : return true if child process terminated bya a signal
WTERMSIG(status)    : return the number of the signal that caused the termination
WIFEXITED(status)   : return true if child terminated normally
WEXITSTATUS(status) : return the exit status ex: exit(EXIT_SUCCESS) = 0
WCOREDUMP(status)   : return true if the child produced a core dump
WIFSTOPPED(status)  : return true if a child was stopped by delivery of a signal
WSTOPSIG(status)    : return the number of the signal that caused the child to stop
WIFCONTINUED(status): return true if the child process was resumed by delivery of SIGCONT signal
*/