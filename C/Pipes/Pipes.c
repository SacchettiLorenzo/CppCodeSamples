#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define NUM_PROC 8
#define NUM_ITER 100
#define READ_BUF_SIZE 5 /* try varying this */

int main()
{
    pid_t child_pid;
    int my_pipe[2];
    int i, j, status;
    char *buf;
    ssize_t num_bytes;

    pipe(my_pipe);

    for (i = 0; i < NUM_PROC; i++)
    {
        switch (fork())
        {
        case -1:
            exit(EXIT_FAILURE);
        case 0:
            close(my_pipe[0]); // closing reading side
            dprintf(1, "WRITER (PID %6d): START writing to pipe\n", getpid());
            for (j = 0; j < NUM_ITER; j++)
            {
                /* The message over the pipe is 25 bytes so it should fit the buffer for all the iterations*/
                dprintf(my_pipe[1],"CHILD PID %6d:  j=%3d\n", getpid(), j);
            }
            dprintf(1, "WRITER (PID %6d): END writing to pipe\n", getpid());

            /* Now the write end can be closed as well */
            close(my_pipe[1]);
            exit(EXIT_SUCCESS);
            break;
        default:
			break;
        }
    }


    close(my_pipe[1]);
	
	/* Allocated read buffer */
	buf = malloc(READ_BUF_SIZE);

	dprintf(1, "READER (PID %6d): START reading from pipe\n", getpid());
	while (num_bytes = read(my_pipe[0], buf, READ_BUF_SIZE)) {
		write(1, buf, num_bytes);
	}
	dprintf(1, "READER (PID %6d): END reading from pipe\n", getpid());
	/* De-allocate read buffer */
	free(buf);
	/* done with reading */
	close(my_pipe[0]);
	
	/* Now let's wait for the termination of all kids */
	while ((child_pid = wait(&status)) != -1) {
		printf("PARENT: PID=%d. Got info of child with PID=%d, status=0x%04X\n", getpid(), child_pid,status);
	}
	
	exit(EXIT_SUCCESS);

}

/*

pipe allow unidirectional comunication between process

once it is created a pipe can be shared with the child process simply using fork

pipe[0] is always the reading side
pipe[1] is always the writing side

the process that is doing one thing (reading or writing) cannot to the other one
so it must close the other pipe end.

a pipe can hold a specific ammount of data in a first in first out queue
this ammount can be obtained with the macro READ_BUFFER_SIZE

in the example the child will only write and parent will only read

in this example the writer and readers perform actions in a not predictible time
that is totally due to the scheduler of the system so the output might be messy.

the important things to figure out is that the reader will be called only once
and the writer are exactly NUM_PROC. writing and reading are happening virtually at the same time.
mind that the writing function do not print on the console but only the reading one does it after 
pulling a chunk of date from the pipe.

read() return the number of byte read, it should return at the first \n so 
it might be called multiple to collect all the data.
The actual data are stored in a buffer

*/