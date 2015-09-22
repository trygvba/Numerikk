// Struct for triadiagonal matrices, and solving if
// diagonally dominant.
#ifndef TRIDIAG_H
#define TRIDIAG_H

class TriDiagMat {
public:
	TriDiagMat(double* d, double* c, double* a, int num);
	bool is_diag_dominant();

private:
	int dim;
	double* subdiag;
	double* diag;
	double* superdiag;
};

#endif // TRIDIAG_H
