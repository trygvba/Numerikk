#include <iostream>
#include "tridiag.h"

using namespace std;

int main(){

	double* d = new double[3];
	double* c = new double[2];
	double* a = new double[2];

	d[0] = 3;
	d[1] = 3;
	d[2] = 3;
	c[0] = 1;
	c[1] = 1;
	a[0] = 1;
	a[1] = 1;
	int n = 3;

        // Initializing matrix
	TriDiagMat test1(d,c,a,n);

        // Printing matrix
	test1.print_tridiag();

        // Testing if it's strictly diagonally dominant
        cout << "\nIs the matrix strictly diagonally dominant?" << endl;
        if(test1.is_diag_dominant()){
          cout << "\tYes" << endl;
        }
        else {
          cout << "\tNo" << endl;
        }
	return 0;
}
