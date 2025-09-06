#ifndef __CUDACC__  
#define __CUDACC__
#endif

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

//4 thread per block
const int THREADS = 4;
const int BLOCKS = 4;

//16 threads in total

//Section of the kogge_stone algorithm, set how many element a thread have to consider at each iteration
const int SECTION_SIZE  = BLOCKS; //in this way the number of threads is equals to the number of section elements


/*INIT A 16 ELEMENTS ARRAY*/

void scan(float* X, float* Y, int input_size) {
	

	

	Kogge_stone_scan_kernel << <BLOCKS, THREADS >> > (/*INSERT HERE PARAMS*/, SECTION_SIZE);
}

__global__ void Kogge_stone_scan_kernel(float* X, float* Y, int input_size) {
	//kogge stone algorith is a parallel scan algorith
	//the main goal is to assign thread the duty evolve the contents of the neightbour element
	//at every iteration the number of element to evolve decrease because we are reaching the main goal
	//the operation converge in the final result that is the sum of all the element on the left of the considered element
	//valid for both exclusive and inclusive scan

	__shared__ float XY[SECTION_SIZE];
	//CONTINUE THE CODE AT PAGE 180
}

int main() {
	
}

//parallel scan are used to convert sequential operations into parallel operations.
//if an operation is naturally described as a mathematical recursion can likely be parallelized.
//such operation must be binary associative, it cannot depend on the order of the operands

/* Inclusive scan
*  A -> A
*  B -> A + B
*  C -> A + B + C
*  ...
*  H -> A + B + ... + H
*/

/* Exclusive scan
* A -> 0
* B -> A
* C -> A + B
* D -> A + B + C
* H -> A + B + ... + G
*/

