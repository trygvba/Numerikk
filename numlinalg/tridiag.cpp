//: tridiagmat.cpp
#include <iostream>
#include "tridiag.h"

using namespace std;

TriDiagMat::TriDiagMat(double* d, double* c, double* a, int n){
	dim = n;
	diag = d;
	superdiag = c;
	subdiag = a;
}

bool TriDiagMat::is_diag_dominant(){
	return true;
}

// Uses iostream
void TriDiagMat::print_tridiag(){
	cout << "The diagonal is the following:" << endl;
	for(int i=0; i<dim; i++){
		cout << diag[i] << " ";
	}
	cout << endl;

	cout << "The subdiagonal: " << endl;
	for(int i=0; i<(dim-1); i++){
		cout << subdiag[i] << " ";
	}

	cout << endl;

	cout << "The superdiagonal: " << endl;
	for (int i=0; i<(dim-1); i++){
		cout << superdiag[i] << " ";
	}
	cout << endl;
}

