
#include "atmosphere/atmosphere.h"

atmosphere earth;
CUmodule atmosphere_module;

int main(const int argc, const char* argv[]) {

	cuInit(0);
	
	CUresult error;
	error = cuModuleLoad(&atmosphere_module, "./atmosphere_kernels.ptx");

	earth.init(true, true);
	earth.init_functions(atmosphere_module);

	return 0;
}