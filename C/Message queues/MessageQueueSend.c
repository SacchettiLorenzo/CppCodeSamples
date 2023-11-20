#include "common.h"

int main(int argc, char* argv[]){
    int q_id;
    struct msgbuf msg;

    if (argc <= 1) {
		fprintf(stderr, "Must specify an integer >0 as message type\n");
		return(-1);
	}

    q_id = msgget(MY_KEY, IPC_CREAT | 0600);
    //0600??????

    //message construction
    msg.mtype = atol(argv[1]);

    if (msg.mtype <= 0) {
		fprintf(stderr, "Must specify an integer >0 as message type\n");
		return(-1);
	}
	printf("Enter the text to send below:\n");
	fgets(msg.mtext, MSG_LEN, stdin);

    /* now sending the message */
	msgsnd(q_id, &msg, MSG_LEN, 0);
	/*	id of the queue
		pointer to message buffer
		max lenght of the message


	*/
	printf("(PID=%d): Q_id=%d: msg type=%ld \"%s\" SENT\n",
	       getpid(), q_id, msg.mtype, msg.mtext);

	return(0);
}

/* 	ERROR CODE
	EACCES 	The calling process does not have write permission to the message queue
	EAGAIN
	EIDRM 	The message queue was removed
	EINTR 	The process caught a signal while waiting on a blocking msgsnd() or msgrcv() call
	ENOMEM	System limit reached 	
	E2BIG	System limit reached
*/

/*	IPC spec
	IPC_PRIVATE Create a total new object, IPC_CREAT is discarded 
	IPC_CREAT Create the message queue if not exist or get the existing one, return the id of the queue
	IPC_NOWAIT if there is not enought space for the message in the queue it return -1 with errno = WAGAIN
	IPC_EXCL Cuase msgget() to fail if the key specified already had an associated id.
	IPC_RCVTYPEID create a queue that can only be read from a process that has the same id of message type
	IPC_SNDTYPEPID create a queue that can only be writted form a process that has the same id of the message type
	S_IROTH permits other users the read access
	S_IWOTH permits other users the write access
	S_IRUSR - S_IWUSR - S_IRGRP - S_IWGRP permit access to matching user or group
*/

