#include <iostream>
#include "tridiag.h"

using namespace std;

int main(){

	double* d = new double[3];
	double* c = new double[2];
	double* a = new double[2];

	d[0] = 1;
	d[1] = 1;
	d[2] = 1;
	c[0] = 1;
	c[1] = 1;
	a[0] = 1;
	a[1] = 1;
	int n = 3;

	TriDiagMat test1(d,c,a,n);

	test1.print_tridiag();
	return 0;
}
