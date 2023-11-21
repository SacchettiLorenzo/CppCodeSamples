#include "common.h"
#include <sys/time.h>
#include <signal.h>
#include <time.h>

#define CHECK_FOR_CONNCECTION_INTERVAL 2000
#define BROADCAST_INTERVAL 500

#define CLOCKID CLOCK_REALTIME
#define SIG SIGUSR1



timer_t connection_timer;
timer_t broadcast_timer;
int common;
int *queues;
int queuesCounter = 0;
struct publicMsgBuf publicMsg;
struct privateMsgBuf privateMsg;
int received;
int maxConnections;
struct itimerspec connectionTimer;
struct sigaction alarm_handler;
struct sigaction sigusr_handler;
struct itimerspec broadcastTimer;

struct sigevent sigalarm;
struct sigevent sigusr;

void boot();
void waitForConnection();
void handle_alarm();
void handle_sigusr();
void broadcast();

int main(int argc, char *argv[])
{
    boot(atoi(argv[1]));
    common = msgget(PUBLIC_KEY, IPC_CREAT | 0600);
    while (1)
    {
        
    }
}

void boot(int maxCon)
{
    maxConnections = maxCon;
    publicMsg.mtype = publicMsgType;
    privateMsg.mtype = privateMsgType;
    queues = (int *)malloc(sizeof(int) * maxCon);

    /*alarm handler for connection*/
    bzero(&alarm_handler, sizeof(alarm_handler));
    alarm_handler.sa_handler = handle_alarm;
    sigaction(SIGALRM, &alarm_handler, NULL);

    /*siguser handler for broadcast*/
    bzero(&sigusr_handler, sizeof(sigusr_handler));
    sigusr_handler.sa_handler = handle_sigusr;
    sigaction(SIGUSR1, &sigusr_handler, NULL);

    /*setup signal event alarm*/
    sigalarm.sigev_notify = SIGEV_SIGNAL;
    sigalarm.sigev_signo = SIGALRM;
    sigalarm.sigev_value.sival_ptr = &connection_timer;
    timer_create(CLOCKID, &sigalarm, &connection_timer);

    /*setup signal event siguser*/
    sigusr.sigev_notify = SIGEV_SIGNAL;
    sigusr.sigev_signo = SIGUSR1;
    sigusr.sigev_value.sival_ptr = &broadcast_timer;
    timer_create(CLOCKID, &sigusr, &broadcast_timer);

    /*setup connection timer*/
    connectionTimer.it_value.tv_sec = CHECK_FOR_CONNCECTION_INTERVAL / 1000;
    connectionTimer.it_value.tv_nsec = 0;
    connectionTimer.it_interval = connectionTimer.it_value;
    timer_settime(connection_timer, 0, &connectionTimer, NULL);

    /*setup broadcast timer*/
    broadcastTimer.it_value.tv_sec = 0;
    broadcastTimer.it_value.tv_nsec = 500000000;
    broadcastTimer.it_interval = broadcastTimer.it_value;
    timer_settime(broadcast_timer, 0, &broadcastTimer, NULL);

}

void waitForConnection()
{
    write(1,"waiting\n",8);
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
        connectionTimer.it_value.tv_sec = 0;
        connectionTimer.it_value.tv_nsec = 0;
        connectionTimer.it_interval = connectionTimer.it_value;
        timer_settime(connection_timer, 0, &connectionTimer, NULL);
    }
}

void handle_alarm()
{
    waitForConnection();
}

void handle_sigusr(){
    broadcast();
    //write(1,"sigusr\n",7);
}

void broadcast(){
    
}