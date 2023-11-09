#define _GNU_SOURCE    // NECESSARY from now on 
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> // per usare sigaction(), sig*() 


//handler for the incoming signals
void handle_signal(int signal);

int main() {
	struct sigaction sa;
	int i;
	
	printf("My pid is: %d\n", getpid());
	bzero(&sa, sizeof(sa));  
	
	sa.sa_handler = handle_signal;
	sigaction(SIGUSR1, &sa, NULL);
	
    printf("process running\n");
	sleep(5);
    printf("now the process is paused\n");
    pause();

	for (;;) {
		printf("received signal so the process is running\n");
        sleep(3);
	}
}

void handle_signal(int signal) {
	
	printf("Got signal #%d: %s\n", signal, strsignal(signal));
}

/*
pause function will pause the process for an infinite ammount of time 
the process will keep on running the moment it receive a signal.
*/

