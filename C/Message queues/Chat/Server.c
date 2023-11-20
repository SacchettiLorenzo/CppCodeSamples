#include "common.h"
#include <sys/time.h>
#include <signal.h>
#define INTERVAL 2000

int common;
int *queues;
int queuesCounter = 0;
struct publicMsgBuf publicMsg;
struct privateMsgBuf privateMsg;
int received;
int maxConnections;
struct itimerval it_val;
struct sigaction sa;


void boot();
void waitForConnection();
void handle_signal();

int main(int argc, char *argv[])
{
    boot(atoi(argv[1]));
    common = msgget(PUBLIC_KEY, IPC_CREAT | 0600);
    while (1)
    {
        //keep computing something
    }
}

void boot(int maxCon)
{
    maxConnections = maxCon;
    queues = (int *)malloc(sizeof(int) * maxCon);
    bzero(&sa, sizeof(sa));
    sa.sa_handler = handle_signal;
    sigaction(SIGALRM, &sa, NULL);
    it_val.it_value.tv_sec = INTERVAL / 1000;
    it_val.it_value.tv_usec = (INTERVAL * 1000) % 1000000;
    it_val.it_interval = it_val.it_value;
    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1)
    {
        perror("error calling setitimer()");
        exit(1);
    }
}

void waitForConnection()
{
    printf("waiting\n");
    if (queuesCounter < maxConnections)
    {
        received = msgrcv(common, &publicMsg, PUBLICMSGLEN, publicMsgType, IPC_NOWAIT);
        
        if (received >= 0)
        {
            *(queues + queuesCounter) = msgget(atoi(publicMsg.mtext), IPC_CREAT | 0600);
            sprintf(privateMsg.mtext,"connected with server");
            msgsnd(*(queues+queuesCounter),&privateMsg,PRIVATEMSGLEN,0);
            queuesCounter++;
            printf("new connection on with pid: %d\n", atoi(publicMsg.mtext));
        }
    }
    else
    {
        char s[] = "Server stop waiting for connection";
        write(1,s,strlen(s));
        it_val.it_value.tv_sec = 0;
        it_val.it_value.tv_usec = 0;
        it_val.it_interval = it_val.it_value;
        setitimer(ITIMER_REAL, &it_val, NULL);
    }
}

void handle_signal()
{
    waitForConnection();
}