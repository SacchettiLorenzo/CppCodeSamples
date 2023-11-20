#include "common.h"
#include <stdlib.h>

int common;
struct publicMsgBuf publicMsg;
void connection(){
    publicMsg.mtype = MSGTYPE;
    sprintf(publicMsg.mtext,"%d",getpid());
    common = msgget(PUBLIC_KEY, IPC_CREAT | IPC_NOWAIT | IPC_EXCL);
    msgsnd(common, &publicMsg, PUBLICMSGLEN, 0);
}

int main(int argc, char *argv[]){
    connection();
}