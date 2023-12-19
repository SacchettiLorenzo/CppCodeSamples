#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    /*start simulation menu*/
    /*logging precision menu*/
    /*inibitore menu*/
    /*chose inibition number*/

    if (system("gnome-terminal -- ./master.out") != -1)
    {
        write(1, "called master on new terminal\n", 30);
    }else{
        write(1, "you need to start the master to perform any operation\n", 54);
    }

    /*print menu now*/
}