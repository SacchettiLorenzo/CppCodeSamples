#include "../include/common.h"

double random1, random2;
int randomAtomNumber;

void Write(int fd, const void *buff, size_t len, processType pType)
{
    snprintf(writeBuffer, WRITE_BUFFER_LEN, "%s%s%s%s", precolor, colors[pType], (char *)buff, blank);
    write(fd, writeBuffer, WRITE_BUFFER_LEN);
    bzero(&writeBuffer, WRITE_BUFFER_LEN);
}

int normalDistributionNumberGenerator(int n_atom_max)
{
    /*Using Box-Muller Transformation*/
    randomAtomNumber = 0;
    while (randomAtomNumber < 1 || randomAtomNumber > n_atom_max)
    {
        random1 = (double)rand() / (double)RAND_MAX;
        random2 = (double)rand() / (double)RAND_MAX;
        if ((int)random1 + (int)random2 % 2 == 0)
        {
            randomAtomNumber = (n_atom_max / 2) + abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
        }else{
            randomAtomNumber = (n_atom_max / 2) - abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
        }
    }

    return randomAtomNumber;
}
