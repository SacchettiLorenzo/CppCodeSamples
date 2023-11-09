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
	
	// Print pid, so that we can send signals from other shells 
	printf("My pid is: %d\n", getpid());
	
	bzero(&sa, sizeof(sa));  // set all bytes to zero 
	// a pointer to the function handling the signal 
	sa.sa_handler = handle_signal;
	
	// NSIG is a macro set to the number of signals 
	printf("Setting the my handler to handle all first %d signals\n", NSIG);
	for (i=0; i<NSIG; i++) {
        //assign an handler for all the signals possible
		if (sigaction(i, &sa, NULL) == -1) {
			fprintf(stderr,"Cannot set a user-defined handler for Signal #%d (%s)\n", i, strsignal(i));
		}
	}
	
	for (;;) {
		printf("Sleeping for ~3 seconds\n");
		sleep(3);
	}
}

void handle_signal(int signal) {
	
	printf("Got signal #%d: %s\n", signal, strsignal(signal));
}

/*
this programm set a user nefined handler for avery signal that the user can handle
the one that cannot be handled are specified in cli due to an error 

to send some signal to the programm it is possible to use htop utility with the 
kill function (send every type of signal)(testing purposes)
*/

/* the most used signals are
#define SIGHUP                 1
#define SIGINT                 2
#define SIGQUIT                 3
#define SIGILL                 4
#define SIGTRAP                 5
#define SIGABRT                 6
#define SIGIOT                 6
#define SIGBUS                 7
#define SIGFPE                 8
#define SIGKILL                 9
#define SIGUSR1                10
#define SIGSEGV                11
#define SIGUSR2                12
#define SIGPIPE                13
#define SIGALRM                14
#define SIGTERM                15
#define SIGSTKFLT        16
#define SIGCHLD                17
#define SIGCONT                18
#define SIGSTOP                19
#define SIGTSTP                20
#define SIGTTIN                21
#define SIGTTOU                22
#define SIGURG                23
#define SIGXCPU                24
#define SIGXFSZ                25
#define SIGVTALRM        26
#define SIGPROF                27
#define SIGWINCH        28
#define SIGIO                29
*/
