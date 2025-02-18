
#include "cuda_runtime.h"

#include "device_launch_parameters.h"
#include "device_atomic_functions.h"



#include <stdio.h>



__global__ void addKernel(int *a)
{
    atomicAdd(a, 20);
    //atomicSub(a, 20);
    //atomicExch(a, 20);
    //atomicMin(a, 20);
    //atomicMax(a, 20);
    //atomicInc(a, 20);
    //atomicDec(a, 20);
    //atomicCas(a, 20);
    //atomicAnd(a, 20);
    //atomicOr(a, 20);
    //atomicXor(a, 20);

}

int main()
{
    //size = 1

    int A = 10;
    int B;

    //pointer to A
    int* cudaA = 0;

    // allocating and copying memory
    cudaMalloc(&cudaA, sizeof(A));
    cudaMemcpy(cudaA, &A, sizeof(A), cudaMemcpyHostToDevice);


    addKernel << <1, 1 >> > (cudaA);

    cudaMemcpy(&B, cudaA,sizeof(B), cudaMemcpyDeviceToHost);

    printf("result %d\n", B);
    

    return 0;
}

