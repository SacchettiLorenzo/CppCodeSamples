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
long MSGTYPE = 1;
#define PUBLICMSGLEN 6
struct publicMsgBuf{
    long mtype;
    char mtext[PUBLICMSGLEN];
};

#define TEST_ERROR    if (errno) {fprintf(stderr, \
					  "%s:%d: PID=%5d: Error %d (%s)\n", \
					  __FILE__,			\
					  __LINE__,			\
					  getpid(),			\
					  errno,			\
					  strerror(errno));}

#endif