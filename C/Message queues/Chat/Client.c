#include "common.h"

int common;
int private;
struct publicMsgBuf publicMsg;
void connection(){
    publicMsg.mtype = MSGTYPE;
    sprintf(publicMsg.mtext,"%d",getpid());
    common = msgget(PUBLIC_KEY,IPC_CREAT | 0600);
    TEST_ERROR;
    msgsnd(common, &publicMsg, PUBLICMSGLEN, 0);
    private = msgget(getpid(),IPC_CREAT | 0600);
    ///TEST_ERROR;
}

int main(int argc, char *argv[]){
    connection();
}