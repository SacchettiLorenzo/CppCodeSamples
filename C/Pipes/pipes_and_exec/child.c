#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

struct INFO
{
    int a;
    int b;
    int c;
};

int main()
{
    struct INFO* info;
    ssize_t num_bytes;
    char buf[30];
    int my_pipe[2];

    if (pipe(my_pipe) == -1)
    {
        perror("error on pipe");
    };

    close(my_pipe[1]);
    num_bytes = read(my_pipe[0], info, sizeof(struct INFO));

    if (num_bytes >= 0)
    {
         bzero(buf, 30);
        snprintf(buf, 30, "num byte %ld\n",num_bytes);
        write(1, buf, 30); 

        bzero(buf, 30);
        snprintf(buf, 30, "%d %d %d\n", info->a, info->b, info->c);
        write(1, buf, 30);
    }
    
    close(my_pipe[0]);
    write(1, "pausing\n", 8);
    pause();
}