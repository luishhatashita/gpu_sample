cmake_minimum_required (VERSION 2.8)

project (sample_openMP)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -fopenmp -pg")
set (source_dir "${PROJECT_SOURCE_DIR}/../src/")

file (source_files "${source_dir}/allocate.cpp" "${source_dir}/field.cpp" "${source_dir}/parallel_omp.cpp")

add_executable (sample_openMP ${source_files})
