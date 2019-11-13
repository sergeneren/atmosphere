cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)
project(ATMOSPHERE LANGUAGES CXX CUDA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include(${CMAKE_SOURCE_DIR}/Helpers.cmake)

## Set output directories

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/atmosphere/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/atmosphere/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/atmosphere/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/atmosphere/bin)

##################################################################

file( GLOB_RECURSE HEADERS "*.h")
file( GLOB_RECURSE CUDA_SOURCES "*.cu")
file( GLOB_RECURSE SOURCE_CPP "*.cpp")

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
	INCLUDE "${CMAKE_CURRENT_SOURCE_DIR},${_VCPKG_INCLUDE_DIR},${CMAKE_CURRENT_SOURCE_DIR}/common,${CMAKE_CURRENT_SOURCE_DIR}/gpu_vdb" 
	OPTIONS -arch=compute_30 -code=sm_30 --ptxas-options=-v -O3 --use_fast_math --maxrregcount=128)

###################################################################	

add_executable(atmosphere ${SOURCE_FILES})

target_link_libraries(atmosphere cuda cudart)