#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>

__constant__ float constData[256];
__device__ float devData;
__device__ float devPointer;

void __constant__access();
__global__ void __constant__Access();

void __device__access();
__global__ void __device__Access();

void page_locked_memory();

int main() {
	//try page 28 code
	/*linear memory access */


	__constant__access();
	__device__access();
}

void __constant__access() {
	/*Constant memory is a global read-only cache which content can be broadcasted to multiple threads in a block.
	* every thread can access the data at the same time.
	* this variable reside in constant memory space and has the lifetime of the application
	* the referemce can be accessed from the host with cudaGetSymbolAddress() and cudaGetSymbolSize() but 
	* it is not possible to access the content of the pointer because it is in the device memory space
	*/

	float hostData[256];
	//populating hostData with progressive numbers
	for (size_t i = 0; i < 256; i++)
	{
		hostData[i] = i;
	}

	//copy hostData to constData
	cudaMemcpyToSymbol(constData, hostData, sizeof(hostData));

	//pupulating hostData with 0
	for (size_t i = 0; i < 256; i++)
	{
		hostData[i] = 0;
	}

	//every thread write the thread number in constData
	__constant__Access << < 16, 16 >> > ();

	//copy constData to hostData
	cudaMemcpyFromSymbol(hostData, constData, sizeof(hostData));
	std::cout << constData[10];

	size_t size;
	cudaGetSymbolSize(&size, constData);
	float* ptr;
	cudaGetSymbolAddress((void**) & ptr, constData);

}

__global__ void __constant__Access() {
	int tid = (blockIdx.x * blockDim.x) + threadIdx.x;
	constData[tid] = tid;
}

void __device__access() {
	/*the __device__ variable and pointer exist only in the GPU global memory space*/
	/*do not mind the visual studio errors*/
	float value = 3.14f;
	cudaMemcpyToSymbol(devData, &value, sizeof(float));
	__device__Access<<<16, 16>>>();
	cudaMemcpyFromSymbol(&value, devData, sizeof(float));

	float* ptr;
	cudaMalloc(&ptr, sizeof(float));
	cudaMemcpyToSymbol(devPointer, &ptr, sizeof(ptr));
	
}

__global__ void __device__Access() {
	devData = 1234.56f;
}

void page_locked_memory() {
	/*page locked memory can be used by any device in the system
	* the driver tracks this portion of virtual memory and automatically accelerates copy functions
	* the memory pages wont change untill they exist in some CUDA context
	*/

	float* ptr;

	//The memory returned by this call will be considered as pinned memory by all CUDA contexts
	cudaHostAlloc(&ptr, sizeof(float), cudaHostAllocPortable);

	//Maps the allocation into the CUDA address space; this memory block has now 2 pointers.
	// cudaHostAlloc() return host pointer, cudaHostGetDevicePointer() return device pointer
	//since the memory are accessible from host and device they must be syncronized to avoid fail in critical section
	cudaHostAlloc(&ptr, sizeof(float), cudaHostAllocMapped);

	//Free the L1 and L2 cache after writing so this memory should be used only for writing because it makes reading worse
	cudaHostAlloc(&ptr, sizeof(float), cudaHostAllocWriteCombined);
}