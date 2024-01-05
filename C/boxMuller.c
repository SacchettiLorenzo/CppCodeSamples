#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    srand(time(NULL));
    /*Using Box-Muller Transformation*/
    int randomAtomNumber = 0;
    double random1, random2;
    int n_atom_max = 3000;

        for(int i = 0; i < 6000; i++){

        random1 = (double)rand() / (double)RAND_MAX;
        random2 = (double)rand() / (double)RAND_MAX;
        if ((int)rand()  % 2 == 0)
        {
            randomAtomNumber = (n_atom_max / 2) + abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
        }else{
            randomAtomNumber = (n_atom_max / 2) - abs((int)(100 * (sqrt(-2 * log(random1)) * cos(2 * 3.14 * random2))));
        }

        printf("%d\n", randomAtomNumber);
        }
    
}

/*compile with gcc boxMuller.c -lm
*/