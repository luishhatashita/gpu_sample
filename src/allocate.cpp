#include "allocate.h"

void allocate1d(int nx, int ny, double*& newarr) 
{
	newarr = new double[nx*ny];
}

void allocate2d(int nx, int ny, double**& newarr) 
{
	double** arr = new double*[nx];
	arr[0] = new double[nx*ny];
	for (int i=1; i<nx; i++) {
		//arr[i] = new double[ny];
		arr[i] = &arr[0][i*ny];
	}
	newarr = arr;
}

void deallocate1d(double*& arr) 
{
	delete[] arr;
}

void deallocate2d(int nx, double**& arr)
{
	//for (int i=0; i<nx; i++) {
	//	delete [] arr[i];
	//}
	delete[] arr[0];
	delete[] arr;
}
