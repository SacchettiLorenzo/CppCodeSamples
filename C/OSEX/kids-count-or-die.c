#define _GNU_SOURCE
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int args, char *argv[])
{
    int timeout = atoi(argv[1]);
    int n_iter = atoi(argv[2]);
    int n_kids = atoi(argv[3]);
    int status;

    for (int i = 0; i < n_kids; i++)
    {
        switch (fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;
        case 0:
            execve("count-loop.out", argv, NULL);
            exit(1);
        }
    }
    pid_t pid;
    while (( pid = wait(&status)) != -1)
    {
        printf("pid %d exited with status %d\n",pid,WEXITSTATUS(status));
    }
}
