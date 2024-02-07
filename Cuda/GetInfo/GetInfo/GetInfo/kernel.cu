
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

using namespace std;




int main()
{
	int device;
	cudaGetDevice(&device);

	struct cudaDeviceProp props;

	cudaGetDeviceProperties(&props, device);

	cout << "shared memory per block : " << props.name << endl;
	
	cout << "max thread per block: " << props.maxThreadsPerBlock << endl;
	cout << "max block per multiprocessor: " << props.maxBlocksPerMultiProcessor << endl;
	cout << "number of multiprocessor : " << props.multiProcessorCount << endl;
	cout << "max number of thread in total : " << props.multiProcessorCount * props.maxBlocksPerMultiProcessor * props.maxThreadsPerBlock << endl;

	cout << "max thread block dimension x : " << props.maxThreadsDim[0] << endl;
	cout << "max thread block dimension y : " << props.maxThreadsDim[1] << endl;
	cout << "max thread block dimension z : " << props.maxThreadsDim[2] << endl;
	cout << "max grid size x: " << props.maxGridSize[0] << endl;
	cout << "max grid size y: " << props.maxGridSize[1] << endl;
	cout << "max grid size z: " << props.maxGridSize[2] << endl;
	
	cout << "IPC support: " << props.ipcEventSupported << endl;

	cout << "shared memory per block : " << props.sharedMemPerBlock<< endl;
	cout << "shared memory per multiprocessor : " << props.sharedMemPerMultiprocessor << endl;

	cout << "L2 cache size: " << props.l2CacheSize << endl;
	cout << "persisting L2 cache max size: " << props.persistingL2CacheMaxSize << endl;
	cout << "access policy max window size: " << props.accessPolicyMaxWindowSize << endl;
	
	cout << "compute capability: " << props.computeMode << endl;

	


}


