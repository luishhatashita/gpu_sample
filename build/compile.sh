#!usr/bin/bash

if [ $# -ge 1 ]; then
	if [ $1 -eq 1 ];  then
		GPROF_OUT=baseline_prof g++ -pg -o baseline.x ../src/baseline.cpp
	elif [ $1 -eq 2 ]; then
		GPROF_OUT=parallel_prof g++ -fopenacc -march=native -pg -o parallel.x ../src/parallel.cpp -fopt-info-all=parallel_comp.txt
	elif [ $1 -eq 3 ]; then
		GPROF_OUT=kernel_prof g++ -fopenacc -march=native -pg -o kernel.x ../src/kernel.cpp -fopt-info-all=kernel_comp.txt
	elif [ $1 -eq 4 ]; then
		GPROF_OUT=parallel_prof_1d g++ -fopenacc -march=native -pg -o parallel_1d.x ../src/parallel_1d_arrays.cpp -fopt-info-all=parallel_comp_1d.txt
	elif [ $1 -eq 5 ]; then
		#g++ -fopenmp -pg -o parallel_omp.x ../src/parallel_omp.cpp -fopt-info-all=parallel_comp_omp.txt
		GPROF_OUT=parallel_prof_omp g++ -fopenmp -march=native -pg -o parallel_omp.x ../src/parallel_omp.cpp -fopt-info-all=parallel_comp_omp.txt
	elif [ $1 -eq 6 ]; then
		GPROF_OUT=baseline_prof_1d g++ -pg -o baseline_1d.x ../src/baseline_1d_arrays.cpp
	fi
else
	message="Input the options 1, 2 or 3 for baseline, parallel and kernel \
constructor compiling, respectively."
	echo "$message"
fi
