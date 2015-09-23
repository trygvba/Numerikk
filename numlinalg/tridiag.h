// Struct for triadiagonal matrices, and solving if
// diagonally dominant.
#ifndef TRIDIAG_H
#define TRIDIAG_H

class TriDiagMat {
public:
	TriDiagMat(double* d, double* c, double* a, int num);
	bool is_diag_dominant();
	bool is_solveable();
	void print_tridiag();
	void trifactor();
	bool is_lu_factored();

private:
	int dim;
	double* subdiag;
	double* diag;
	double* superdiag;
	bool lu_factored;
};

#endif // TRIDIAG_H
