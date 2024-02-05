
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

void vector_init(int* vector_ptr, int size);
__global__ void vectorAdd(int* a, int* b, int* c, int n);

int main()
{
    int n = 1 << 16;

    //host vector pointers
    int* h_a, * h_b, * h_c;

    //device vector pointers
    int* d_a, * d_b, * d_c;

    size_t bytes = sizeof(int) * n;

    //allocate host memory
    h_a = (int*)malloc(bytes);
    h_b = (int*)malloc(bytes);
    h_c = (int*)malloc(bytes);

    //allocate device memory
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);

    //initialize vectors with random values
    vector_init(h_a, n);
    vector_init(h_b, n);

    //comy memory from host to device
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);

    int NUM_THREAD = 256; // Arbitrary decided

    int NUM_BLOCKS = (int)ceil(n / NUM_THREAD);

    vectorAdd << <NUM_BLOCKS, NUM_THREAD >> > (d_a, d_b, d_c,n);

    cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost);

    for (size_t i = 0; i < n; i++)
    {
        std::cout << h_a[i] << " + " << h_b[i] << " = " << h_c[i] << std::endl;
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


