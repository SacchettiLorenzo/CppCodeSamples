#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_KIDS 20

int main(int argc, char *argv[])
{

    int value;
    int status;

    srand(getpid());

    for (int i = 0; i < NUM_KIDS; i++)
    {
        switch (value = fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            /* Perform actions specific to child */
            srand(getpid());
            // printf("%d",rand);
            exit(rand() % 6 + 1);
            break;

        default:
            /* Perform actions specific to parent */
            break;
        }
    }

    int sum = 0;
    while ((wait(&status)) != -1)
    {
        sum += WEXITSTATUS(status);
    }
    printf("sum: %d\n", sum);

    exit(EXIT_SUCCESS);
}