#include <cmath>
#include <random>
#include "field.h"

void initializeField1d(int nx, int ny, double*& arr, double* bc, double fill) 
{
	// fixed random seed generator;
	mt19937 gen(42);
	uniform_real_distribution<double> dis(-fill, fill);
	for (int i = 1; i < nx-1; i++) {
		for (int j = 1; j < ny-1; j++) {
			arr[i*ny + j] = dis(gen);
			//if (i % 1000 == 0 && j % 1000 == 0) {
			//	cout << mat[i*ny + j] << ",";
			//}
		}
	}
	for (int i = 0; i < nx; i++) {
		arr[i*ny]    	   = bc[0];
		arr[i*ny + ny - 1] = bc[2];
	}
	for (int j = 0; j < ny; j++) {
		arr[j]             = bc[3];
		arr[(nx-1)*ny + j] = bc[1];
	}
}

void initializeField2d(int nx, int ny, double**& arr, double* bc, double fill) 
{
	// fixed random seed generator;
	mt19937 gen(42);
	uniform_real_distribution<double> dis(-fill, fill);
	for (int i = 1; i < nx-1; i++) {
		for (int j = 1; j < ny-1; j++) {
			arr[i][j] = dis(gen);
			//if (i % 1000 == 0 && j % 1000 == 0) {
			//	cout << mat[j][i] << ",";
			//}
		}
	}
	for (int i = 0; i < nx; i++) {
		arr[i][0]    = bc[0];
		arr[i][ny-1] = bc[2];
	}
	for (int j = 0; j < ny; j++) {
		arr[0][j]    = bc[3];
		arr[nx-1][j] = bc[1];
	}
}

void computeField1d(int nx, int ny, double*& arr, double*& arrnew, double& error) 
{
	double localerror = error;
	#pragma acc parallel loop reduction(max:localerror)
	for(int i=1; i<nx-1; i++)
	{
		#pragma acc loop reduction(max:localerror)
		for(int j=1; j<ny-1; j++)
		{
			arrnew[i*ny + j] = 0.25 * (arr[i*ny + (j+1)] + arr[i*ny + (j-1)]
								  	  +arr[(i-1)*ny + j] + arr[(i+1)*ny + j]);
			localerror = fmax(localerror, fabs(arrnew[i*ny + j] - arr[i*ny + j]));
		}
	}
	error = localerror;
}

void computeField2d(int nx, int ny, double**& arr, double**& arrnew, double& error) 
{
	#pragma omp parallel for reduction(max:error)
	#pragma acc parallel loop reduction(max:error)
	for(int i=1; i<nx-1; i++)
	{
		#pragma acc loop reduction(max:error)
		for(int j=1; j<ny-1; j++)
		{
			arrnew[i][j] = 0.25 * (arr[i][j+1] + arr[i][j-1]
								  +arr[i-1][j] + arr[i+1][j]);
			error = fmax(error, fabs(arrnew[i][j] - arr[i][j]));
		}
	}
}

void updateField1d(int nx, int ny, double*& arr, double*& arrnew)
{
	#pragma acc parallel loop
	for(int i=1; i<nx-1; i++)
	{
		#pragma acc loop
		for(int j=1; j<ny-1; j++)
		{
			arr[i*ny + j] = arrnew[i*ny + j];
		}
	}
}

void updateField2d(int nx, int ny, double**& arr, double**& arrnew)
{
	#pragma omp parallel for
	#pragma acc parallel loop
	for(int i=1; i<nx-1; i++)
	{
		#pragma acc loop
		for(int j=1; j<ny-1; j++)
		{
			arr[i][j] = arrnew[i][j];
			//if (i % 1000 == 0 && j % 1000 == 0) {
			//	cout << mat[j][i] << ",";
			//}
		}
	}
	//cout << endl;
}
