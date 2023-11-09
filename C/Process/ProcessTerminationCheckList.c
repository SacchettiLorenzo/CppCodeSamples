#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILD 5
typedef enum
{
    false,
    true
} bool;

struct checkList
{
    pid_t pid[NUM_CHILD];
    bool check[NUM_CHILD];
}

checkList(struct checkList *list)
{
    for (size_t i = 0; i < NUM_CHILD; i++)
    {
        if (list->check[i] == true)
            printf("Process with pid: %d terminated\n", list->pid[i]);
        else
            printf("Process with pid: %d is not terminated\n", list->pid[i]);
    }
}

int main()
{
    pid_t my_pid, my_ppid, value;
    bool exec = false;
    int exec2 = false;

    pid_t child_pid;
    int status;
    int forked = 0;

    struct checkList list;
    for (size_t i = 0; i < NUM_CHILD; i++)
    {
        list.check[i] = false;
    }

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
            forked++;

            list.pid[i] = value;
            if (exec == false)
            {
                printf("PARENT: PID=%d, PPID=%d, fork_value=%d\n", my_pid, my_ppid, value);
                exec = true;
            }

            //this segment is executed when all the child are forked
            if (forked == NUM_CHILD)
            {
                while ((child_pid = wait(&status)) != -1)
                {
                    for (size_t i = 0; i < NUM_CHILD; i++)
                    {
                        if (list.pid[i] == child_pid)
                            list.check[i] = true;
                    }
                }

                if (exec2 == false)
                {
                    checkList(&list);
                    exec2 = true;
                }
            }

            break;
        }
    }
    /* Both child and parent process will execute here!! */
    exit(EXIT_SUCCESS);
}

/*
in this case the parent will wait for all the child to be forked
then and only then will start waiting 
the check list is filled as soon as the child process with the corresponding pid exit or return
*/
