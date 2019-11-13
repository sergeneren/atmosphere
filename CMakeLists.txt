cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)
project(ATMOSPHERE LANGUAGES CXX CUDA)

set(CMAKE_INCLUDE_CURRENT_DIR ON)


file( GLOB_RECURSE HEADERS "*.h")
file( GLOB_RECURSE CUDA_SOURCES "*.cu")
file( GLOB_RECURSE SOURCE_CPP "*.cpp")

set(SOURCE_FILES
	${HEADERS}
	${CUDA_SOURCES}
	${SOURCE_CPP})
	
add_executable(atmosphere ${SOURCE_FILES})

target_compile_options(vdb_convert PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-gencode arch=compute_30,code=sm_30>)