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
struct Client
{
    int queues;
    int pid;
};

struct Client *clients;

int queuesCounter = 0;
struct publicMsgBuf publicMsg;
struct privateMsgBuf privateMsgRcv;
struct privateMsgBuf privateMsgSend;
int received;
int maxConnections;
struct itimerspec connectionTimer;
struct sigaction alarm_handler;
struct sigaction sigusr_handler;
struct itimerspec broadcastTimer;

struct sigevent sigalarm;
struct sigevent sigusr;

void boot(int);
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
    privateMsgRcv.mtype = privateMsgTypeServerRcv;
    privateMsgSend.mtype = privateMsgTypeServerSend;
    clients = (struct Client *)malloc(sizeof(struct Client) * maxCon);


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
    write(1, "waiting\n", 8);
    if (queuesCounter < maxConnections)
    {
        received = msgrcv(common, &publicMsg, PUBLICMSGLEN, publicMsgType, IPC_NOWAIT);

        if (received > 0)
        {
            (clients + queuesCounter)->queues = msgget(atoi(publicMsg.mtext), IPC_CREAT | 0600);
            (clients + queuesCounter)->pid = atoi(publicMsg.mtext);
            sprintf(privateMsgSend.mtext, "connected with server\n");
            if (msgsnd((clients + queuesCounter)->queues, &privateMsgSend, PRIVATEMSGLEN, 0) == 0)
            {
                kill((clients + queuesCounter)->pid, SIGUSR1);
            }
            queuesCounter++;
            printf("new connection on with pid: %d\n", atoi(publicMsg.mtext));
        }
    }
    else
    {
        char s[] = "Server stop waiting for connection";
        write(1, s, strlen(s));
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

void handle_sigusr()
{
    broadcast();
}

void broadcast()
{
    for (size_t i = 0; i < queuesCounter; i++)
    {
        received = msgrcv((clients + i)->queues, &privateMsgRcv, PRIVATEMSGLEN, privateMsgTypeServerRcv, 0);
        if (received > 0)
        {
            strcpy(privateMsgSend.mtext, privateMsgRcv.mtext);
            for (size_t j = 0; j < queuesCounter; j++)
            {
                if (j != i)
                {
                    if (msgsnd((clients + j)->queues, &privateMsgSend, PRIVATEMSGLEN, 0) == 0)
                    {
                        kill((clients + j)->pid, SIGUSR1);
                    }
                }
                printf("sending: %s to %d\n", privateMsgSend.mtext, (clients + j)->pid);
            }
        }
    }
}