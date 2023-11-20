#ifndef __IPC_MSG_SMALIB_H__
#define __IPC_MSG_SMALIB_H__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define PUBLIC_KEY 0X111111
#define MSGTYPE 1
#define PUBLICMSGLEN 5
struct publicMsgBuf{
    long mtype;
    char mtext[PUBLICMSGLEN];
};

#endif