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
	lu_factored = false;
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

void TriDiagMat::trifactor(){
	if(!lu_factored){
		// u=d, and l=a, c is kept constant.
		for(int k=0; k<(dim-1); k++){
			subdiag[k] = subdiag[k]/diag[k];
			diag[k+1] = diag[k+1] - subdiag[k]*superdiag[k];
		}
	}
	else if(lu_factored){
		for(int k=dim-1; k>0; k--){
			diag[k] = subdiag[k-1]*superdiag[k-1]+diag[k];
			subdiag[k-1] = subdiag[k-1]*diag[k-1];
		}
	}

	lu_factored = !(lu_factored);
}

bool TriDiagMat::is_lu_factored() {return lu_factored;}

