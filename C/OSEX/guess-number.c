#define _GNU_SOURCE
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void handle_signal(int signal);
int main(int argc, char *argv[])
{
    int numberToGuess = atoi(argv[1]);
    int timeout = atoi(argv[2]);

    int number;
    struct sigaction sa;
    bzero(&sa, sizeof(sa)); 
    sa.sa_handler = handle_signal;
    sigaction(SIGALRM, &sa, NULL);

    alarm(timeout);

    while (1)
    {
        printf("guess number: \n");
        scanf("%i", &number);
        if (number > numberToGuess)printf("maggiore\n");
        if (number < numberToGuess)printf("minore\n");
        if (number == numberToGuess)
        {
            printf("got it\n");
            exit(EXIT_SUCCESS);
        }
    }
}

void handle_signal(int signal){
    printf("timout reached\n");
    exit(EXIT_FAILURE);
}