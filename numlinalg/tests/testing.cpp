#include <iostream>
#include "tridiag.h"

using namespace std;

// Short function for print vector:
void print_vec(double* b, int n){
  for(int i=0; i<n; i++){
    cout << b[i] << " ";
  }
  cout << endl;
}



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

  // Testing the LU-factorisation:
  cout << "\nIs the matrix LU-factored?" << endl;
  if(test1.is_lu_factored()){
    cout << "\tYes" << endl;
  }
  else {
    cout << "\tNo" << endl;
  }

  // Do the LU-factorization:
  test1.trifactor();
  // Print the matrix:
  cout << "LU-factorization of the matrix: " << endl;
  test1.print_tridiag();

  // And we again check the LU-factorization
  cout << "\nIs the matrix LU-factored now?" << endl;
  if(test1.is_lu_factored()){
    cout << "\tYes" << endl;
  }else {
    cout << "\tNo" << endl;
  }

  //Let's factor back:
  test1.trifactor();
  cout << "Hoperfully, we've factored back. Let's see..." << endl;
  test1.print_tridiag();
	
  // Let's try to solve a small system:
  double* b = new double[3];
  b[0] = 1;
  b[1] = 1;
  b[2] = 1;

  cout << "\nWant to solve system with RHS: " << endl;
  print_vec(b, n);

  cout << "\nThe solution is: " << endl;
  test1.trisolve(b);
  print_vec(b, n);

  return 0;
}
