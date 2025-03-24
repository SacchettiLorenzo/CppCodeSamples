#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

//matrix with metadata information
typedef struct {
    int width;
    int height;
    int stride;
    float* elements;
} Matrix;

// __device__ function can only be called from __global__ or __device__ functions
//get and set a matrix element value
__device__ float GetElement(const Matrix A, int row, int col) {
    return A.elements[row * A.stride + col];
}

__device__ void SetElement(const Matrix A, int row, int col, float value) {
    A.elements[row * A.stride + col] = value;
}

//submatrix with BLOCK_SIZE X BLOCK_SIZE dimension
__device__ Matrix GetSubMatrix(Matrix A, int row, int col) {
    Matrix Asub;
    Asub.width = BLOCK_SIZE;
    Asub.height = BLOCK_SIZE;
    Asub.stride = A.stride;
    Asub.elements = &A.elements[A.stride * BLOCK_SIZE * row + BLOCK_SIZE * col]; //Pointer to the element of the Matrix where the subset start (the matrix in memory is linear)
    return Asub;
}

//actula gpu operations
__global__ void MatMulKernel(Matrix A, Matrix B, Matrix C) {

    // block row and column
    int blockRow = blockIdx.y;
    int blockCol = blockIdx.x;

    //each threadblock compute one sumbmatrix
    Matrix Csub = GetSubMatrix(C, blockRow, blockCol);

    float Cvalue = 0;

    //thread row and column withing Csub
    int row = threadIdx.y;
    int col = threadIdx.x;

    //loop over the entire matrix (note that non square matrix may need some adjustment for correct manipulation)
    for (int m = 0; m < (A.width / BLOCK_SIZE); ++m) {
        // A,B submatrix
        Matrix Asub = GetSubMatrix(A, blockRow, m);
        Matrix Bsub = GetSubMatrix(B, m, blockCol);

        //shered memory for A,B submatrix
        __shared__ float As[BLOCK_SIZE][BLOCK_SIZE];    
        __shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];  

        // each thread load one element of each submatrix
        As[row][col] = GetElement(Asub, row, col);
        Bs[row][col] = GetElement(Bsub, row, col);

        //make sure that all submatrix are loaded
        __syncthreads();

        for (int  e = 0; e < BLOCK_SIZE; ++e)
        {
            Cvalue += As[row][e] * Bs[e][col];
        }

        //make sure that  preceding computation is done before loading two new submatrix
        __syncthreads();
    }

    SetElement(Csub, row, col, Cvalue);
}

//host code for matrix multiplication
void MatMul(const Matrix A, const Matrix B, Matrix C) {
    //create and allocate Matrix in device memory
    Matrix d_A;
    d_A.width = d_A.stride = A.width;
    d_A.height = A.height;
    size_t size = A.width * A.height * sizeof(float);
    cudaMalloc(&d_A.elements, size);
    cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);

    Matrix d_B;
    d_B.width = d_B.stride = B.width;
    d_B.height = B.height;
    size = B.width * B.height * sizeof(float);
    cudaMalloc(&d_B.elements, size);
    cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

    Matrix d_C;
    d_C.width = d_C.stride = C.width;
    d_C.height = C.height;
    size = C.width * C.height * sizeof(float);
    cudaMalloc(&d_C.elements, size);

    //invoke kernel
    dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 dimGrid(B.width / dimBlock.x, B.height / dimBlock.y);
    MatMulKernel << <dimGrid, dimBlock >> > (d_A, d_B, d_C);

    //read C from device memory
    cudaMemcpy(C.elements, d_C.elements, size, cudaMemcpyDeviceToHost);

    //free memory
    cudaFree(d_A.elements);
    cudaFree(d_B.elements);
    cudaFree(d_C.elements);
}

Matrix InitMatrix(bool k) {
    int n = 1 << 10;
    Matrix K;
    K.height = 0;
    K.width = 0;
    K.stride = 0;
    K.elements = (float*)malloc(n * n * sizeof(float));

    if(k)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            K.elements[i * n + j] = rand() % 100;
            
        }
    }

    return K;
}


int main()
{
    //1 initiate matrix with random numbers
    //0 only memory allocation
    Matrix A, B, C;
    A = InitMatrix(1);
    B = InitMatrix(1);
    C = InitMatrix(0);
    

    MatMul(A, B, C);

    return 0;
}

// Helper function for using CUDA to add vectors in parallel.
