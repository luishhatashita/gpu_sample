#include <iostream>
#include "allocate.h"
#include "field.h"

using namespace std;

int main () {
	// Parameters:
	double tol;
	double error;
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
	double* A;
	double* Anew;
	allocate1d(n, m, A);
	allocate1d(n, m, Anew);
	double bc[4] = {u_S, u_E, u_N, u_W};

	initializeField1d(n, m, A, bc, fill);

	cout << "Jacobi iterator for: " << n << "x" << m 
		 << " mesh" << endl;
	error = 1.0;
	iter = 1;
	while ( error > tol && iter < iter_max )
	{
		error = 0.0;

		computeField1d(n, m, A, Anew, error);

		updateField1d(n, m, A, Anew);

		if(iter % 50 == 0) printf("%5d, %0.6f\n", iter, error);

		iter++;
	}

	deallocate1d(A);
	deallocate1d(Anew);

	cout << "end" << endl;
	return 0;
}
