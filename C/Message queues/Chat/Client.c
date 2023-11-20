#include "common.h"

int common;
int private;
int received;

struct publicMsgBuf publicMsg;
struct privateMsgBuf privateMsg;

void connection(){
    publicMsg.mtype = publicMsgType;
    privateMsg.mtype = privateMsgType;
    sprintf(publicMsg.mtext,"%d",getpid());
    common = msgget(PUBLIC_KEY,IPC_CREAT | 0600);
    TEST_ERROR;
    msgsnd(common, &publicMsg, PUBLICMSGLEN, 0);
    private = msgget(getpid(),IPC_CREAT | 0600);
    ///TEST_ERROR;
}

int main(int argc, char *argv[]){
    connection();
    received = msgrcv(private, &privateMsg, PRIVATEMSGLEN, privateMsgType,0);
        
        if (received >= 0)
        {
            printf("message: %s\n", privateMsg.mtext);
        }
}