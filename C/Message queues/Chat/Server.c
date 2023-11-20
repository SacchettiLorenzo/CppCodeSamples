#include "common.h"

int common;
int *queues;
int queuesCounter = 0;
struct publicMsgBuf publicMsg;
int received;
int maxConnections;
void boot(int maxConnectionsreceivedfromArg){
    maxConnections = maxConnectionsreceivedfromArg;
    queues = (int*)malloc(sizeof(int) * maxConnectionsreceivedfromArg);
}

void waitForConnection()
{
    printf("waiting\n");
    while (1)
    {
        received = msgrcv(common, &publicMsg, PUBLICMSGLEN, MSGTYPE, 0);
        TEST_ERROR;
        if (received >= 0)
        {
            *(queues+queuesCounter) = msgget(atoi(publicMsg.mtext), IPC_CREAT | 0600);
            queuesCounter++;
            printf("new connection on with pid: %d\n",atoi(publicMsg.mtext));
        }else{
            //break;
        }
    }


}

int main(int argc, char *argv[])
{
    boot(atoi(argv[1]));

    common = msgget(PUBLIC_KEY, IPC_CREAT |0600);
    printf("%d\n",common);
    TEST_ERROR;
    waitForConnection();
}