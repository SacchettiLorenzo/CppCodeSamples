#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

if(argc < 2)exit(-1);

char* file = argv[1];
int n_kids = atoi(argv[2]);
int n_writes = atoi(argv[3]);
int value;
int status;

FILE * my_file ;
my_file = fopen (file , "w" );

//setvbuf ( my_file , NULL , _IONBF , 0) ;

for (int i = 0; i < n_kids; i++)
    {
        switch (value = fork())
        {
        case -1:
            /* Handle error */
            fprintf(stderr, "Error #%03d: %s\n", errno, strerror(errno));
            break;

        case 0:
            /* Perform actions specific to child */
             pid_t my_pid = getpid();   // get current process pid

             for (size_t i = 0; i < n_writes; i++)
             {
                fprintf(my_file,"%d\n" ,my_pid);
             }
             exit(EXIT_SUCCESS);
            

        default:
            /* Perform actions specific to parent */
            
            //adding wait will sync the process to work in the cration order
            /*
            while ((wait(&status)) != -1){
                //wait for all the child process to terminate and exit before termination of the parent
            }
            */

            break;
        }
    }

    fclose(my_file);
    exit(EXIT_SUCCESS);
}