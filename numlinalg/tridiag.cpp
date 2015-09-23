//: tridiagmat.cpp
#include <iostream>
#include "tridiag.h"
#include <cmath>

using namespace std;

TriDiagMat::TriDiagMat(double* d, double* c, double* a, int n){
	dim = n;
	diag = d;
	superdiag = c;
	subdiag = a;
}


// uses cmath
bool TriDiagMat::is_diag_dominant(){
  bool diagdom = true;
  double temp;
  
  // go through each row and check
  for (int i=0; i<dim; i++){
    if(i==0) temp = abs(superdiag[i]);
    else if (i==(dim-1)) temp = abs(subdiag[i-1]);
    else temp = abs(subdiag[i-1])+abs(superdiag[i]);

    diagdom = (diag[i]>temp);

    // if false, break and return
    if (!diagdom) break;
  }
  return diagdom;
    

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

