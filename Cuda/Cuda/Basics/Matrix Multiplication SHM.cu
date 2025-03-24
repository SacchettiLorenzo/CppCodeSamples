// this version of the matrix multiplication use shared memory
#ifndef __CUDACC__  
#define __CUDACC__
#endif
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define THREAD_BLOCK_SIZE 16

typedef struct {
	int width;
	int height;
	int stride;
	float* elements;
} Matrix;

__global__ void  MatMulKernel(const Matrix, const Matrix, Matrix);
void matMul(const Matrix A, const Matrix B, Matrix c);
void matrix_init(Matrix* M);

__device__ float GetElement(const Matrix A, int row, int col) {
	return A.elements[row * A.stride + col];
}

__device__ void SetElement(Matrix A, int row, int col, float value) {
	A.elements[row * A.stride + col] = value;
}

__device__ Matrix GetSubMatrix(Matrix A, int row, int col) {
	Matrix Asub;
	Asub.width = THREAD_BLOCK_SIZE;
	Asub.height = THREAD_BLOCK_SIZE;
	Asub.stride = A.stride;
	Asub.elements = &A.elements[A.stride * THREAD_BLOCK_SIZE * row + THREAD_BLOCK_SIZE * col];
	return Asub;
}



int main() {
	srand(time(NULL));

	Matrix A, B;
	A.width = 16;
	A.height = 16;
	B.width = 16;
	B.height = 16;
	matrix_init(&A);
	matrix_init(&B);

	Matrix C;
	C.width = 16;
	C.height = 16;
	C.elements = (float*)malloc(C.width * C.height * sizeof(float));

	matMul(A, B, C);

	for (size_t i = 0; i < C.height; i++)
	{
		for (size_t j = 0; j < C.width; j++)
		{
			std::cout << C.elements[i * C.width + j] << " ";
		}
		std::cout << std::endl;
	}
}
void matMul(const Matrix A, const Matrix B, Matrix C) {
	Matrix d_A;
	d_A.width = A.width;
	d_A.height = A.height;
	d_A.stride = A.width;
	size_t size = A.width * A.height * sizeof(float);
	cudaMalloc(&d_A.elements, size);
	cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);

	Matrix d_B;
	d_B.width = B.width;
	d_B.height = B.height;
	d_B.stride = B.width;
	size = B.width * B.height * sizeof(float);
	cudaMalloc(&d_B.elements, size);
	cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

	Matrix d_C;
	d_C.width = C.width;
	d_C.height = C.height;
	d_C.stride = C.width;
	size = C.width * C.height * sizeof(float);
	cudaMalloc(&d_C.elements, size);

	//Invoke kernel
	dim3 dimBlock(THREAD_BLOCK_SIZE, THREAD_BLOCK_SIZE);
	dim3 dimGrid(B.width / dimBlock.x, A.height / dimBlock.y);
	MatMulKernel << <dimGrid, dimBlock >> > (d_A, d_B, d_C);

	//read result from device memory
	cudaMemcpy(C.elements, d_C.elements, size, cudaMemcpyDeviceToHost);

	//free device memory
	cudaFree(&d_A.elements);
	cudaFree(&d_B.elements);
	cudaFree(&d_C.elements);
}

__global__ void  MatMulKernel(const Matrix A, const Matrix B, Matrix C) {
	int blockRow = blockIdx.y;
	int blockCol = blockIdx.x;

	//each thread block computes one sub-matrix Csub of C
	Matrix Csub = GetSubMatrix(C, blockRow, blockCol);

	//each thread accumulate the result in Cvalue
	float Cvalue = 0;

	//thread row and column
	int row = threadIdx.y;
	int col = threadIdx.x;

	for (size_t m = 0; m < (A.width/THREAD_BLOCK_SIZE); ++m)
	{
		//submatrix of A and B
		Matrix Asub = GetSubMatrix(A, blockRow, m);
		Matrix Bsub = GetSubMatrix(B, m, blockCol);

		//shared memory
		__shared__ float As[THREAD_BLOCK_SIZE][THREAD_BLOCK_SIZE];
		__shared__ float Bs[THREAD_BLOCK_SIZE][THREAD_BLOCK_SIZE];

		//each thread load one element of the sub matrix
		As[row][col] = GetElement(Asub, row, col);
		Bs[row][col] = GetElement(Bsub, row, col);

		//syncronize to make sure sub matrix are loaded
		__syncthreads();

		for (int e = 0; e < THREAD_BLOCK_SIZE; ++e)
		{
			Cvalue += As[row][e] * Bs[e][col];
		}
			
		__syncthreads();
		
	}
		SetElement(Csub, row, col, Cvalue);
}

void matrix_init(Matrix* M) {
	M->elements = (float*)malloc(M->width * M->height * sizeof(float));

	for (size_t i = 0; i < M->height; i++)
	{
		for (size_t j = 0; j < M->width; j++)
		{
			M->elements[i * M->width + j] = rand() % 100;
		}
	}
}
