#define _GNU_SOURCE  
#include<time.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void handle_signal(int signal);

int main(int args, char* argv[]){
    int timeout = atoi(argv[1]);
    int n_iter = atoi(argv[2]);


    struct sigaction sa;
    bzero(&sa, sizeof(sa));  
	sa.sa_handler = handle_signal;
    sigaction(SIGALRM, &sa, NULL);
    
    /*
    clock_t before = clock();
    clock_t difference;
    for (int i = 0; i < n_iter; i++)
    {
        difference = difftime(clock() , before);
        //printf("%li at cycle: %d\n",difference, i);
        if(difference >= timeout)raise(SIGALRM);
    }
    */

   alarm(timeout);
   for (int i = 0; i < n_iter; i++)
   {
    //printf("cycle: %d\n", i);
   }
   
    
}

void handle_signal(int signal){
    //printf("i'm an asshole\n");
    exit(2);
}