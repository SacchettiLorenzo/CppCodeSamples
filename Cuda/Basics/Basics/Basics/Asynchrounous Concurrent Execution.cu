#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>

	__global__ void kernel(int*, int);
int main() {
	const int nStreams = 2;
	int streamSize = 64;
	int blockSize = 16;
	int* d_a;
	cudaMalloc(&d_a, sizeof(int));
	int* a = (int*)malloc(sizeof(int));
	int streamBytes = 0;
	cudaStream_t stream[nStreams];
	for (int i = 0; i < nStreams; i++)
	{
		cudaStreamCreate(&stream[i]);
	}

	/*To implement the concurrent model, instead of calling cudaMemcpy, 
	we call cudaMemcpyAsync and launch kernel with the stream specified so that they will return to the host thread immediately after call.*/
	for (int i = 0; i < nStreams; i++)
	{
		int offset = i * streamSize;
		cudaMemcpyAsync(&d_a[offset], &a[offset], sizeof(int), cudaMemcpyHostToDevice, stream[i]);
		kernel << <streamSize / blockSize, blockSize, 0, stream[i] >> > (d_a, offset);
		cudaMemcpyAsync(&a[offset], &d_a[offset], streamBytes, cudaMemcpyDeviceToHost, stream[i]);
	}

	for (int i = 0; i < nStreams; i++)
	{
		cudaStreamDestroy(stream[i]);
	}

	
}

__global__ void kernel(int* d_a, int) {
	//do somethig 
	*d_a = 10;
}
	/*some operation can be executed at the sime time
	* for example computation on the host, computation on the device and
	* memory tranfer can operate concurrently
	* concurrent operations are managed using streams that are a sequence of command to execute in order
	* 
	* one of the best way to use Async concurrent execution is to overlap data transfer and kernel execution
	* that could be usefull for the problems that can be solved with tiling
	* 
	* streams can be syncronized (even one by one) with the host
	*/

/* 
* continue host functions pag 50
*/