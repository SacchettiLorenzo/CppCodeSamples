#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handle_signal(int signal);

typedef enum
{
    false,
    true
} bool;

int main()
{
    struct sigaction sa;
    sigset_t my_mask; // a set of signal to work with
    bool blocked = false;

    printf("My pid is: %d\n", getpid());
    bzero(&sa, sizeof(sa));
    sa.sa_handler = handle_signal;

    // handling SIGUSR1
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        fprintf(stderr, "Cannot set a user-defined handler ");
    }

    sigemptyset(&my_mask);                  // set an empty mask
    sigaddset(&my_mask, SIGUSR1);           // add SIGUSR1 to the mask

    for (;;)
    {
        printf("Sleeping for ~5 seconds\n");
        sleep(5);

        if (blocked == false)
        {
            // Blocking SIGUSR1
            sigprocmask(SIG_BLOCK, &my_mask, NULL); // mask SIGINT in the process
            printf("Now SIGUSR1 is blocked\n");
            blocked = true;
        }
        else
        {
            // Unblocking now SIGUSR1
            sigprocmask(SIG_UNBLOCK, &my_mask, NULL); // ublock SIGINT
            printf("Now SIGUSR1 is unblocked\n");
            blocked = false;
        }
    }

}
    void handle_signal(int signal)
    {
        printf("Got signal #%d: %s\n", signal, strsignal(signal));
    }

/* blocking and unblocking a signal until a specific event happen
    use htop to send signal

a singal, received while the mask was blocking such signal, remain pending and will be 
handled as soon as the mask stop blocking it.
*/
