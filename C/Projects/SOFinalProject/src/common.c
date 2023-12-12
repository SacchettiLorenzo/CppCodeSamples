#include "../include/common.h"

double random1, random2;
int randomAtomNumber;
int u = 0;

void Write(int fd, const void* buff, size_t len, processType pType){
     snprintf(writeBuffer,WRITE_BUFFER_LEN,"%s%s%s%s",precolor,colors[pType],(char*)buff,blank);
     write(fd,writeBuffer,WRITE_BUFFER_LEN);
     bzero(&writeBuffer, WRITE_BUFFER_LEN);
}

int normalDistributionNumberGenerator(int n_atom_max)
{
    /*FIXME - remove the u and find a good method to have new seed every time*/
    srand ( time(NULL) + u);
    u++;
    if(n_atom_max == 0){
        n_atom_max = N_ATOM_MAX;
    }
    
    /*Using Box-Muller Transformation*/
    randomAtomNumber = 0;
    while (randomAtomNumber < 1 || randomAtomNumber > n_atom_max)
    {
        random1 = (double)rand() / (double)RAND_MAX;
        random2 = (double)rand() / (double)RAND_MAX;
        randomAtomNumber = abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
    }
    
    return randomAtomNumber;
}
