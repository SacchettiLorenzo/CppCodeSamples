// this version of the matrix multiplication does not use shared memory
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
	float* elements;
} Matrix;

__global__ void  MatMulKernel(const Matrix, const Matrix, Matrix);
void matMul(const Matrix A, const Matrix B, Matrix c);
void matrix_init(Matrix* M);

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
	size_t size = A.width * A.height * sizeof(float);
	cudaMalloc(&d_A.elements, size);
	cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);

	Matrix d_B;
	d_B.width = B.width;
	d_B.height = B.height;
	size = B.width * B.height * sizeof(float);
	cudaMalloc(&d_B.elements, size);
	cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

	Matrix d_C;
	d_C.width = C.width;
	d_C.height = C.height;
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
	//each thread computes one element of C by accumulating result into Cvalue
	float Cvalue = 0;
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int col = blockIdx.x * blockDim.x + threadIdx.x;
	for (size_t e = 0; e < A.width; ++e)
	{
		Cvalue += A.elements[row * A.width + e] * B.elements[e * B.width + col];
		C.elements[row * C.width + col] = Cvalue;
	}
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
