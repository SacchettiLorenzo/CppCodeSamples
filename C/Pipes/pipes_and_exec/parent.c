#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TEST_ERROR                                    \
    if (errno)                                        \
    {                                                 \
        fprintf(stderr,                               \
                "%s:%d: PID=%5d: Error %d (%s) %s\n", \
                __FILE__,                             \
                __LINE__,                             \
                getpid(),                             \
                errno,                                \
                strerror(errno),                      \
                strerrorname_np(errno));              \
    }

#define NUM_PROC 8
#define NUM_ITER 100
#define READ_BUF_SIZE 10 /* try varying this */
char *args_0[] = {"./child.out", "", (char *)0};

struct INFO
{
    int a;
    int b;
    int c;
};

pid_t child_pid;

int i, j, status;

int main()
{
    struct INFO *info;
    ssize_t num_bytes;
    char buf[30];
    int my_pipe[2];
    info = malloc(sizeof(struct INFO));
    if (pipe(my_pipe) == -1)
    {
        perror("error on pipe");
    };

    for (i = 0; i < 2; i++)
    {
        write(1, "fork\n", 5);
        switch (fork())
        {
        case -1:
            write(1, "Error1\n", 7);
            exit(EXIT_FAILURE);
        case 0:
            write(1, "forked\n", 7);
            
            
            if (execve(args_0[0], args_0, NULL) == -1)
            {
                write(1, "Error\n", 6);
                exit(EXIT_FAILURE);
            }
            
            exit(EXIT_SUCCESS);
            break;

        default:
            break;
        }
    }

    info->a = 10;
    info->b = 20;
    info->c = 30;
    close(my_pipe[0]);
    for (size_t i = 0; i < 2; i++)
    {
        write(my_pipe[1], info, sizeof(struct INFO));
    }
    close(my_pipe[1]);
    write(1, "writed\n", 7);

    /* Now let's wait for the termination of all kids */
    while ((child_pid = wait(&status)) != -1)
    {
        /*printf("PARENT: PID=%d. Got info of child with PID=%d, status=0x%04X\n", getpid(), child_pid,status);*/
    }

    exit(EXIT_SUCCESS);
}
