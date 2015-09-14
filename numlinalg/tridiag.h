// Struct for triadiagonal matrices, and solving if
// diagonally dominant.
#ifndef TRIDIAG_H
#define TRIDIAG_H

struct TriDiagMat {
	int dim;
	double* subdiag;
	double* diag;
	double* superdiag;

	//
	void initialize(double* d, double* c, double* a, int num);
	bool is_diag_dominant();

};

#endif // TRIDIAG_H
