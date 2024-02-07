
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

__constant__ __device__ int Dvalue = 10;

__constant__ __device__ unsigned int Dvalue_ = 20;
int value = 0;

__global__ void arithmetics(int);

__global__ void checkMemorySpace();


int main() {
	arithmetics << <1, 1 >> > (1);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (2);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (3);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (4);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (5);
	cudaMemcpyFromSymbol(&value, Dvalue_, sizeof(unsigned int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (6);
	cudaMemcpyFromSymbol(&value, Dvalue_, sizeof(unsigned int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (7);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (8);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (9);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (10);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	arithmetics << <1, 1 >> > (11);
	cudaMemcpyFromSymbol(&value, Dvalue, sizeof(int));
	std::cout << value << std::endl;
	checkMemorySpace << <1, 1 >> > ();
}

__global__ void arithmetics(int count) {
	
	switch (count)
	{
	case 1:
	atomicAdd(&Dvalue, 5);
		break;
	case 2:
		atomicSub(&Dvalue, 2);
		break;
	case 3:
		atomicMin(&Dvalue, 8);
		break;
	case 4:
		atomicMax(&Dvalue, 30);
		break;
	case 5:
		atomicInc(&Dvalue_, 30); //if Dvalue <= 30 -> Dvalue++
		break;
	case 6:
		atomicDec(&Dvalue_, 100); //if Dvalue <= 100 -> Dvalue--
		break;
	case 7:
		int compare = 30;
		atomicCAS(&Dvalue, compare, 11); //Compare And Swap:  if Dvalue == 30 -> Dvalue = 11;
		break;
	case 8:
		atomicExch(&Dvalue, 100); //exchange value
		break;
	case 9:
		atomicOr(&Dvalue, 200); 
		break;
	case 10:
		atomicAnd(&Dvalue, 1000); 
		break;
	case 11:
		atomicXor(&Dvalue, 500);
		break;
	default:
		break;
	}
}

__global__ void checkMemorySpace() {
	/*check the address in from a specific memory space*/
	__isGlobal(&Dvalue);
	__isShared(&Dvalue);
	__isConstant(&Dvalue);
	//__isGridConstant(&Dvalue);
	__isLocal(&Dvalue);
}