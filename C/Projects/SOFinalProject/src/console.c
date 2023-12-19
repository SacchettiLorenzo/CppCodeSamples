#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>

int try = 10;
int i;
char buff[128];
pid_t masterPid = 0;

struct timespec Mtime;

FILE *masterPidFile;

void MainMenu();
void SimulationMenu();
void InibitionMenu();
void readKey();

int selection1;
int main(int argc, char *argv[])
{
    Mtime.tv_sec = 0;
    Mtime.tv_nsec = 100000000;
    /*start simulation menu*/
    /*logging precision menu*/
    /*inibitore menu*/
    /*chose inibition number*/

    if (system("gnome-terminal -- ./master.out") != -1)
    {
        write(1, "called master on new terminal\n", 30);
    }
    else
    {
        write(1, "you need to start the master to perform any operation\n", 54);
    }

    for (i = 0; i < try; i++)
    {
        if (system("ps -A | grep master > master.txt") != -1) /*REVIEW - check if command is right*/
        {
            masterPidFile = fopen("master.txt", "r");
            if (masterPidFile == NULL)
            {
                continue;
            }
            else
            {
                while (fgets(buff, sizeof(buff), masterPidFile))
                {
                    sscanf(buff, "%d", &masterPid);
                    printf("master have pid: %d\n", masterPid);
                    i = try;
                    break;
                }
            }
        }
        else
        {
            write(1, "error opening file\n", 18);
            nanosleep(&Mtime, NULL);
        }
    }
    if (system("clear") == -1)
    {
        write(1, "cannot clear\n", 13);
    }
    while (1)
    {
        MainMenu();
    }
}

void MainMenu()
{
    system("clear");
    switch (selection1)
    {
    case 0:
        printf("│%c│ Menu simulazione\n", '+');
        printf("│%c│ Menu inibitore\n", ' ');
        break;
    case 1:
        break;
        printf("│%c│ Menu simulazione\n", ' ');
        printf("│%c│ Menu inibitore\n", '+');
    default:
        break;
    }
}

void SimulationMenu()
{
}
void InibitionMenu()
{
}
