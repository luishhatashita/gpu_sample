//#include <stdio.h>
#include <iostream>
#include <cmath>
#include <random>

using namespace std;

void allocate2d(int nx, int ny, double**& mat) 
{
	double** arr = new double*[nx];
	for (int i=0; i<nx; i++) {
		arr[i] = new double[ny];
	}
	mat = arr;
}

void deallocate2d(int nx, double**& mat)
{
	for (int i=0; i<nx; i++) {
		delete [] mat[i];
	}
	delete[] mat;
}

void initializeField(int nx, int ny, double**& mat, double* bc, double fill) 
{
	// fixed random seed generator;
	mt19937 gen(42);
	uniform_real_distribution<double> dis(-fill, fill);
	for (int i = 1; i < nx-1; i++) {
		for (int j = 1; i < ny-1; i++) {
			mat[i][j] = dis(gen);
			if (i % 1000 == 0 && j % 1000 == 0) {
				cout << mat[j][i] << ",";
			}
		}
	}
	for (int i = 0; i < nx; i++) {
		mat[i][0]    = bc[0];
		mat[i][ny-1] = bc[2];
	}
	for (int j = 0; j < ny; j++) {
		mat[0][j]    = bc[3];
		mat[nx-1][j] = bc[1];
	}
}

void computeField(int nx, int ny, double** mat, double**& matnew, double* perror) 
{
	double local_error = *perror;
	#pragma acc parallel loop reduction(max:local_error)
	for( int j = 1; j < nx-1; j++)
	{
		#pragma acc loop reduction(max:local_error)
		for( int i = 1; i < ny-1; i++ )
		{
			matnew[j][i] = 0.25 * (mat[j][i+1] + mat[j][i-1]
								  +mat[j-1][i] + mat[j+1][i]);
			local_error = fmax(local_error, fabs(matnew[j][i] - mat[j][i]));
		}
	}
	*perror = local_error;
}

void updateField(int nx, int ny, double**& mat, double** matnew)
{
	#pragma acc parallel loop
	for( int j = 1; j < nx-1; j++)
	{
		#pragma acc loop
		for( int i = 1; i < ny-1; i++ )
		{
			mat[j][i] = matnew[j][i];
			//if (i % 1000 == 0 && j % 1000 == 0) {
			//	cout << mat[j][i] << ",";
			//}
		}
	}
	//cout << endl;
}

int main () {
	// Parameters:
	double tol;
	double error;
	double* perror = &error;// = new double;
	int iter, iter_max;
	int n, m;
	double u_S, u_E, u_N, u_W, fill;

	// Initialize parameters;
	tol = 0.001;
	iter_max = 1001;
	n = 4096;
	m = n;
	u_S = 0.0;
	u_E = 0.0;
	u_N = 0.0;
	u_W = 0.0;
	fill = 100.0;
	
	// Initialize the field:
	double** A;
	double** Anew;
	allocate2d(n, m, A);
	allocate2d(n, m, Anew);
	double bc[4] = {u_S, u_E, u_N, u_W};

	initializeField(n, m, A, bc, fill);

	cout << "Jacobi iterator for: " << n << "x" << m 
		 << " mesh" << endl;
	error = 1.0;
	iter = 1;
	while ( error > tol && iter < iter_max )
	//while ( (*error) > tol && iter < iter_max )
	{
		//(*error) = 0.0;
		error = 0.0;

		computeField(n, m, A, Anew, perror);
		//for( int j = 1; j < n-1; j++)
		//{
		//	for( int i = 1; i < m-1; i++ )
		//	{
		//		Anew[j][i] = 0.25 * ( A[j][i+1] + A[j][i-1]
		//						    + A[j-1][i] + A[j+1][i]);
		//		error = fmax( error, fabs(Anew[j][i] - A[j][i]));
		//	}
		//}

		updateField(n, m, A, Anew);
		//for( int j = 1; j < n-1; j++)
		//{
		//	for( int i = 1; i < m-1; i++ )
		//	{
		//		A[j][i] = Anew[j][i];
		//		//if (i % 1000 == 0 && j % 1000 == 0) {
		//		//	cout << mat[j][i] << ",";
		//		//}
		//	}
		//}
		////cout << endl;

		if(iter % 50 == 0) printf("%5d, %0.6f\n", iter, error);

		iter++;
	}

	deallocate2d(n, A);
	deallocate2d(n, Anew);
	//delete error;

	cout << "end" << endl;
	return 0;
}
