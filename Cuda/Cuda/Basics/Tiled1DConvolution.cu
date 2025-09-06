#ifndef __CUDACC__  
#define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

__global__ void convolution_1D_tiled_kernel(float* N, float* P, int mask_width, int Width);
__global__ void convolution_1D_tiled_caching_kernel(float* N, float* P, int mask_width, int Width);

//NOT SURE IF THE SISES ARE CORRECT
#define MAX_MASK_WIDTH 3
#define TILE_SIZE 4

typedef struct {
	int size;
	float* elements;
} Array;

Array InitArray(int size, bool isRes) {
	Array K;
	K.size = size;
	

	if (!isRes) {
		K.elements = (float*)malloc(size * sizeof(float));

		for (size_t i = 0; i < size; i++)
		{
			//K.elements[i] = rand() % 100;
			K.elements[i] = i;
		}
	}
	else {
		K.elements = (float*)calloc(size, sizeof(float));
	}

	return K;
}

void convolution_1D_tiled(float* N, float* P, int mask_width, int Width) {

	//4 thread per block
	int THREADS = 4;
	int BLOCKS = Width / THREADS;

	float* N_dev;
	cudaMalloc(&N_dev, Width*sizeof(float));
	cudaMemcpy(N_dev, N, Width*sizeof(float), cudaMemcpyHostToDevice);

	float* P_dev;
	cudaMalloc(&P_dev, Width*sizeof(float));
	//NOT SURE I HAVE TO COPY MEMORY
	cudaMemcpy(P_dev, P, Width*sizeof(float), cudaMemcpyHostToDevice);

	//tiled convolution
	convolution_1D_tiled_kernel << <BLOCKS, THREADS >> > (N_dev, P_dev, mask_width, Width);
	//tiled convolution with constant memory and general caching
	convolution_1D_tiled_caching_kernel << <BLOCKS, THREADS >> > (N_dev, P_dev, mask_width, Width);

	cudaMemcpy(P, P_dev, Width*sizeof(float), cudaMemcpyDeviceToHost);
}

__global__ void convolution_1D_tiled_kernel(float* N, float* P, int mask_width, int Width) {
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	//this shared memory hold the data for the whole block in order to improve memory acces
	//it hold the TILE_SIZE + (MAX_MASK_WIDTH - 1)/2 for each side of the mask 
	// (if the mask is 3 elements, 1 element on the left and 1 on the right of the current element under convolution) 
	__shared__ float N_ds[TILE_SIZE + MAX_MASK_WIDTH - 1];

	int n = mask_width / 2;

	//halo regions are the elements respectively on the left and of the right of the current convolution tile
	int halo_index_left = (blockIdx.x - 1) * blockDim.x + threadIdx.x;
	if (threadIdx.x >= blockDim.x - n) {
		N_ds[threadIdx.x - (blockDim.x - n)] = (halo_index_left < 0) ? 0 : N[halo_index_left];
	}

	N_ds[n + threadIdx.x] = N[blockIdx.x * blockDim.x + threadIdx.x];

	int halo_index_right = (blockIdx.x + 1) * blockDim.x + threadIdx.x;
	if (threadIdx.x < n) {
		N_ds[n + blockDim.x + threadIdx.x] = (halo_index_right >= Width) ? 0 : N[halo_index_right];
	}

	__syncthreads();

	float Pvalue = 0;
	for (size_t j = 0; j < mask_width; j++)
	{
		//Pvalue += N_ds[threadIdx.x + j] * M[j]; //M is a convolution mask (filter or kernel)
		Pvalue += N_ds[threadIdx.x + j] * 1; //for the purpose of the exercises M is constant
	}
	P[i] = Pvalue;
}


__global__ void convolution_1D_tiled_caching_kernel(float* N, float* P, int mask_width, int Width) {
	//take advantage of L1 and L2 caching to store halo cells
	
	int i = blockIdx.x * blockDim.x + threadIdx.x;

	__shared__ float N_ds[TILE_SIZE]; //holds only the internal elements of the tile, halo elements are access in the N parameter that is server by an L2 cache
	N_ds[threadIdx.x] = N[i];
	__syncthreads();

	int This_tile_start_point = blockIdx.x * blockDim.x;
	int Next_tile_start_point = (blockIdx.x + 1) * blockDim.x;
	int N_start_point = i - (mask_width / 2);
	float Pvalue = 0;
	for (size_t j = 0; j < mask_width; j++){
		int N_index = N_start_point + j;
		if (N_index >= 0 && N_index < Width) {
			if ((N_index >= This_tile_start_point) && (N_index < Next_tile_start_point)) {
				//Pvalue += N_ds[threadIdx.x + j - (mask_width / 2)] * M[j];
				Pvalue += N_ds[threadIdx.x + j - (mask_width / 2)] * 1;//for the purpose of the exercises M is constant
			}
			else {
				//Pvalue += N[N_index] * M[j]; //for the purpose of the exercises M is constant
				Pvalue += N[N_index] * 1;
			}
		}
	}
}

int main() {
	Array A;
	Array Res;
	A = InitArray(16, false);
	Res = InitArray(16, true);

	convolution_1D_tiled(A.elements, Res.elements, 3, A.size);

	for (size_t i = 0; i < Res.size; i++)
	{
		std::cout << Res.elements[i] << " ";
	}
}