#ifndef __CUDACC__  
#define __CUDACC__
#endif
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

//shared memory with 16*16 size (int)
const int SHMEM_SIZE  = 1 << 10;
const int N = 1 << 10;

typedef struct {
	int width;
	int height;
	int stride;
	float* elements;
} Matrix;

__global__ void tiledMatrixMul(int* a, int* b, int* c, int n, int tile_size);
void matrix_init(int* matrix_ptr, int size);





int main() {
	//host matrix pointers
	int* h_a, * h_b, * h_c;

	//device matrix pointers
	int* d_a, * d_b, * d_c;

	size_t bytes = sizeof(int) * N * N;

	//allocate host memory
	h_a = (int*)malloc(bytes);
	h_b = (int*)malloc(bytes);
	h_c = (int*)malloc(bytes);

	//allocate device memory
	cudaMalloc(&d_a, bytes);
	cudaMalloc(&d_b, bytes);
	cudaMalloc(&d_c, bytes);

	matrix_init(h_a, N*N);
	matrix_init(h_b, N*N);

	//comy memory from host to device
	cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);

	int THREADS = 32;
	int BLOCKS = N / THREADS;

	dim3 threads(THREADS, THREADS);
	dim3 blocks(BLOCKS, BLOCKS);

	tiledMatrixMul << <blocks, threads >> > (d_a, d_b, d_c,N,16);

	cudaMemcpy(h_c, d_c, bytes, cudaMemcpyDeviceToHost);
}

void matrix_init(int* matrix_ptr, int size) {
	for (size_t i = 0; i < size; i++)
	{
		matrix_ptr[i] = rand() % 100;
	}
}

__global__ void tiledMatrixMul(int* a, int* b, int* c, int n, int tile_size) {

	int temp = 0;

	//two staticallyt-sized pieces of shared memory
	__shared__ int A[SHMEM_SIZE];
	__shared__ int B[SHMEM_SIZE];

	//shorter parameters for clean re-use
	int tx = threadIdx.x;
	int ty = threadIdx.y;
	int bx = blockIdx.x;
	int by = blockIdx.y;

	//calculate global row and column position for this thread
	int row = by * tile_size + tx;
	int col = bx * tile_size + ty;

	for (size_t i = 0; i < (n / tile_size); i++)
	{
		A[(ty * tile_size) + tx] = a[row * n + (i * tile_size + tx)];
		B[(ty * tile_size) + tx] = b[(i * tile_size * n + ty * n) + col];

		//ensure that all thread have loaded their data before proceeding
		__syncthreads();

		for (size_t j = 0; j < tile_size; j++)
		{
			temp += A[(ty * tile_size) + j] * B[(j * tile_size) + tx];
		}

		//ensure that threads that have already finished computing start writing on memory
		__syncthreads();
	}

	c[(row * n) + col] = temp;
}