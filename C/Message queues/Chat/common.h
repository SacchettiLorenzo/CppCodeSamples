#ifndef __IPC_MSG_SMALIB_H__
#define __IPC_MSG_SMALIB_H__
#define _GNU_SOURCE 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define PUBLIC_KEY 0X111111
#define PUBLICMSGLEN 6
#define USERNAMEMAXLEN  30
#define PRIVATEMSGLEN 120

long publicMsgType = 1;
long privateMsgTypeClientSend = 2;
long privateMsgTypeServerRcv = 2;

long privateMsgTypeServerSend = 3;
long privateMsgTypeClientRcv = 3;

struct publicMsgBuf{
    long mtype;
    char mtext[PUBLICMSGLEN];
};

struct privateMsgBuf{
    long mtype;
    char mtext[PRIVATEMSGLEN];
};

#define TEST_ERROR    if (errno) {fprintf(stderr, \
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}

#endif
