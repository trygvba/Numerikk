//: tridiagmat.cpp

#include "tridiag.h"

using namespace std;

TriDiagMat::TriDiagMat(double* d, double* c, double* a, int n){
	dim = n;
	diag = d;
	superdiag = c;
	subdiag = a;
}

bool TriDiagMat::is_diag_dominant(){
	return 1;
}


