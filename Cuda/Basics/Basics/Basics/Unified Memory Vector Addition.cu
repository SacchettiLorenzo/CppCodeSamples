#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>


void vector_init(int* vector_ptr, int size);
__global__ void vectorAdd(int* a, int* b, int* c, int n);

int main() {

    int id = cudaGetDevice(&id);

    int n = 1 << 16;

    size_t bytes = sizeof(int) * n;

    //unified memory pointers
    int* a, * b, * c;

    //allocate unified memory
    cudaMallocManaged(&a, bytes);
    cudaMallocManaged(&b, bytes);
    cudaMallocManaged(&c, bytes);

    vector_init(a, n);
    vector_init(b, n);

    int NUM_THREAD = 256; // Arbitrary decided

    int NUM_BLOCKS = (int)ceil(n / NUM_THREAD);

    //transfer the data to the GPU asyncronously before their use
    cudaMemPrefetchAsync(a, bytes, id);
    cudaMemPrefetchAsync(b, bytes, id);

    vectorAdd << <NUM_BLOCKS, NUM_THREAD >> > (a, b, c, n);
     
    //wait for all the previos operations before using values
    cudaDeviceSynchronize();
     
    //transfer the data back to the CPU asyncronously before their use
    cudaMemPrefetchAsync(b, bytes, cudaCpuDeviceId);

    for (size_t i = 0; i < n; i++)
    {
        std::cout << a[i] << " + " << b[i] << " = " << c[i] << std::endl;
    }
}

void vector_init(int* vector_ptr, int size) {
    for (size_t i = 0; i < size; i++)
    {
        vector_ptr[i] = rand() % 100;
    }
}

__global__ void vectorAdd(int* a, int* b, int* c, int n) {
    //Calculate the global thread ID (tid) used for the calculation as index

    int tid = (blockIdx.x * blockDim.x) + threadIdx.x; //using a specific block with fixed dimension and specific thread inside the block

    if (tid < n) {
        c[tid] = a[tid] + b[tid];
    }
}

/*
* This example does the same operation as the Vector Addition.cu 
* but use the unified memory to automatically manage the memory
* using cuda malloc management the data gets loaded into the gpu after the vectorAdd call causing a page fault
* the unified memory need a syncronization operation after performing operation on the gpu.
* 
* to perform the transfer before the vectorAdd call is possible to run a pre-feth operation asyncronously
* the same happen when using the data that shoud be transfered from the gpu to the cpu on call
* 
* cudaMemPrefetchAsync send the data to the gpu/cpu before their actual use to avoid page fault
*/