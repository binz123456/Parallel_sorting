cmake_minimum_required(VERSION 3.10)
project(parallel_sorting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -fopenmp")

add_executable(parallel_sorting
    src/main.cpp
)

# Link OpenMP (CMake's find is optional; flags above also add it)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
  target_link_libraries(parallel_sorting PUBLIC OpenMP::OpenMP_CXX)
endif()
