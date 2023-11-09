#define _GNU_SOURCE    
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h> 
#include <time.h>

#define		SEC_TO_SLEEP	10

//handler for the incoming signals
void handle_signal(int signal);

int main() {
	struct sigaction sa;
    struct timespec this_time, next_time, diff_time;
    
	printf("My pid is: %d\n", getpid());
	bzero(&sa, sizeof(sa));  
	sa.sa_handler = handle_signal;
    sigaction(SIGUSR1, &sa, NULL);

    /* Setting the sleep time */
	this_time.tv_sec = SEC_TO_SLEEP;
	this_time.tv_nsec = 0;
	
	for (;;) {
		printf("Sleeping for ~10 seconds\n");
		int ret_val = nanosleep(&this_time, &next_time);

        if(ret_val == 0){
            printf("completed sleeping\n");
        }else{
			
            printf("Signal! remaining time to sleep: %ld\n",next_time.tv_nsec);
        }
	}
}

void handle_signal(int signal) {
	
	printf("Got signal #%d: %s\n", signal, strsignal(signal));
}

/*
nanosleep() use a systemcall to gether the current time.
the systemcall provide the time in nanosecond directly for a system timer.
it is more precise than the sleep() function that only provide seconds.

nanosleep() return -1 if interrupted by a signal, if not it returns 0
&this_time provide the structure with the ammount of time to wait
&next_time provide the remaining time if the function gets interrupted (can be used to call nanosleep again)
*/


