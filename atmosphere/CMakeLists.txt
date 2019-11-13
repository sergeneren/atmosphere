##################################################################

file( GLOB HEADERS "${CMAKE_SOURCE_DIR}/atmosphere/*.h")
file( GLOB CUDA_SOURCES "${CMAKE_SOURCE_DIR}/atmosphere/*.cu")
file( GLOB SOURCE_CPP "${CMAKE_SOURCE_DIR}/atmosphere/*.cpp")

set(SOURCE_FILES
	${HEADERS}
	${CUDA_SOURCES}
	${SOURCE_CPP})
	
## Add custom build command for cuda files 

find_program(CUDA_NVCC_EXECUTABLE nvcc)
message ( STATUS "Build CUDA kernels: ${CUDA_SOURCES}" )
_COMPILEPTX ( SOURCES ${CUDA_SOURCES} 
	TARGET_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} 
	GENERATED CUDA_PTX GENPATHS CUDA_PTX_PATHS 
	INCLUDE "${CMAKE_SOURCE_DIR}, ${CMAKE_SOURCE_DIR}/atmosphere, ${CMAKE_SOURCE_DIR}/atmosphere/common" 
	OPTIONS -arch=compute_30 -code=sm_30 --ptxas-options=-v -O3 --use_fast_math --maxrregcount=128)

###################################################################	

add_executable(atmosphere ${SOURCE_FILES})

target_link_libraries(atmosphere cuda cudart)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/atmosphere/common)