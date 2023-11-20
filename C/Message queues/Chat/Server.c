#include "common.h"

int common;
int *queues;
int queuesCounter = 0;
struct publicMsgBuf publicMsg;
int received;
void boot(int maxConnections){
    queues = (int*)malloc(sizeof(int) * maxConnections);
}

void waitForConnection()
{
    while (true)
    {
        received = msgrcv(common, &publicMsg, PUBLICMSGLEN, MSGTYPE, 0);
        if (received >= 0)
        {
            break;
        }
    }

    *(queues+queuesCounter) = msgget(atoi(publicMsg.mtext), IPC_CREAT | IPC_NOWAIT | IPC_EXCL);

}

int main(int argc, char *argv[])
{
    boot(atoi(argv[1]));

    common = msgget(PUBLIC_KEY, IPC_CREAT | IPC_NOWAIT | IPC_EXCL);
    waitForConnection();
}