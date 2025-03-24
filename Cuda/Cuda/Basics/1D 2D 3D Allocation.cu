#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

void allocation_1_Dimension();
void allocation_2_Dimension();
void allocation_3_Dimension();
__global__ void someFunction2D(int* mem_segment, size_t pitch, int width, int height);
__global__ void someFunction3D(cudaPitchedPtr mem_segment, int width, int height, int depth);

int main() {
	//allocation_2_Dimension();
	allocation_3_Dimension();
}

void allocation_1_Dimension() {
	int size = 10;
	int* mem_segment;

	cudaMalloc(&mem_segment, size * sizeof(int));

	for (size_t i = 0; i < size; i++)
	{
		mem_segment[i] = rand() % 100;
	}
}

void allocation_2_Dimension() {
	int width = 64; 
	int height = 64;

	int* mem_segment;
	size_t pitch;
	cudaMallocPitch(&mem_segment, &pitch, width * sizeof(int), height);
	//std::cout <<"pitch: "<< pitch << std::endl;
	someFunction2D<< <100, 512 >> > (mem_segment, pitch, width, height);
}

void allocation_3_Dimension() {
	int width = 64;
	int height = 64;
	int depth = 64;

	cudaExtent extent = make_cudaExtent(width * sizeof(float),height, depth); //sizes of multidimensional array in linear memory
	cudaPitchedPtr mem_segment; //3D memory pointer
	cudaMalloc3D(&mem_segment, extent);
	someFunction3D << <100, 512 >> > (mem_segment, width, height,depth);
	
}

__global__ void someFunction2D(int* mem_segment, size_t pitch, int width, int height) {
	//accessig element in 2D array using given allignement
	for (size_t i = 0; i < height; i++)
	{
		int* row = (int*)((char*)mem_segment + i * pitch);
		for (size_t j = 0; j < width; ++j)
		{
			int element = row[j];
		}
	}
}

__global__ void someFunction3D(cudaPitchedPtr mem_segment, int width, int height, int depth){
	//accessig element in 3D array using given allignement
	char* mem = (char*)mem_segment.ptr;
	size_t pitch = mem_segment.pitch;
	size_t slicePitch = pitch * height;
	for (size_t z = 0; z < depth; z++)
	{
		char* slice = mem + z + slicePitch; //2D array at index z
		for (size_t y = 0; y < height /*(mem_segment.ysize)*/; y++)
		{
			float* row = (float*)(slice + y * pitch); //1D array at index y
			for (size_t x = 0; x < width /*(mem_segment.xsize)*/; x++)
			{
				float element = row[x]; //elemet at index x
			}
		}
	}

}

/*
* cudaMallocPitch() and cudaMalloc3D() are reccomended for allocations of 2D and 3D array 
* as it make sure that the allocation in appropriatly padded to meet the allignement requirement
* the returned pith must be used to access array element
* the mem_segment type can be changed
* cudaMallocPitch() make sure that the memory is allocated as a 2D array with (width * pitch) byte as width
* CudaMalloc3D() make sure that the memory is allocated as a 3D array, the dimesion are stored in a cudaExtend structure
* the overall size is given by width*sizeof(type). the ammount of byte for height and depth are calculated accordingly
* to access a 3D array we must slice the 3D structure in simpler 2D arrays then in rows.
*/