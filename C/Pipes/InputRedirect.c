#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int out_fd, new_fd;

    /* open a file in write mode with options for file management*/
    if ((out_fd = open("myfile.txt",O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
    {
        fprintf(stderr, "Error %d (%s) when opening file \"%s\"\n",
                errno,
                strerror(errno),
                "myfile.txt");
        exit(EXIT_FAILURE);
    }

    new_fd = dup2(out_fd, 1);
    fprintf(stderr, "Writing data to fd=%d, will actually write to fd=%d\n",new_fd, out_fd);
}