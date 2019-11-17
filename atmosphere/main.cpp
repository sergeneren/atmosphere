
#include "atmosphere/atmosphere.h"

#define __CUDA_RUNTIME_H__

#include <cuda.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include "helper_cuda.h"

atmosphere earth;
CUmodule atmosphere_module;
CUcontext ctx;
CUdevice device;

#define check_success(expr) \
    do { \
        if(!(expr)) { \
            fprintf(stderr, "Error in file %s, line %u: \"%s\".\n", __FILE__, __LINE__, #expr); \
            exit(EXIT_FAILURE); \
        } \
    } while(false)

int main(const int argc, const char* argv[]) {

	// Set the device with maximum capacity 
	int deviceid = gpuGetMaxGflopsDeviceId();
	check_success(cudaSetDevice(deviceid) == cudaSuccess);
	cuInit(deviceid);

	// get device id and create context
	cudaGetDevice(&device);
	cuCtxCreate(&ctx, 0, device);

	CUresult error;
	error = cuModuleLoad(&atmosphere_module, "atmosphere_kernels.ptx");
	if (error != CUDA_SUCCESS) printf("Error: unable to load cuda module! %d", error);
	
	earth.init(atmosphere_module, true, true);
	return 0;
}