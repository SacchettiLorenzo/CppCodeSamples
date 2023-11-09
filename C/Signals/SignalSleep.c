#define _GNU_SOURCE    
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <time.h>

//handler for the incoming signals
void handle_signal(int signal);

int main() {
	struct sigaction sa;
    
	printf("My pid is: %d\n", getpid());
	bzero(&sa, sizeof(sa));  
	sa.sa_handler = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);
	
	for (;;) {
		printf("Sleeping for ~10 seconds\n");
		int remaining_time = sleep(10);
        printf("%d\n",remaining_time);
	}
}

void handle_signal(int signal) {
	
	printf("Got signal #%d: %s\n", signal, strsignal(signal));
}

/*
this programm shows that every time the current process is sleeping and receive a signal
it must call the signal handler immediately.
the sleep() function return the ammount of time left to sleep if the process handle a signal
*/


