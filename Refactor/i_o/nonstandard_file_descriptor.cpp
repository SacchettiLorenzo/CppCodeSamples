#include <stdio.h>

int main (int argc, char **argv){
    FILE *fd_3, *fd_4;
    //Open file descriptor 3
    fd_3 = fdopen(3,"r");
    //Open file descriptor 3
    fd_4 = fdopen(4,"w");
    //Read from file descriptoe 3
    char buf[32];
    while(fgets(buf,32,fd_3)!= NULL){
        //Write on file descriptor 4
        fprintf(fd_4,"%s", buf);
    }  

    fclose(fd_3);
    fclose(fd_4);
} 

//This code open and read/write from file descriptor diffrent from stdin and stdout
//run with: ./nonstandard_file_descriptor 3<input.txt 4>&1 to redirect output to stdout

