//: cubicsplineproblem.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "cubicsplineproblem.h"
#include "tridiag.h"

using namespace std;

CubicSplineProblem::CubicSplineProblem(string filename){
  ifstream ifile;
  string temp;  
  int counter=0;

  ifile.open(filename.c_str());
  if (ifile.is_open()){
    // Get interval start
    getline(ifile, temp);
    a = strtod(temp.c_str(),NULL);

    // Get interval end
    getline(ifile, temp);
    b = strtod(temp.c_str(),NULL);

    // Get number of points
    getline(ifile, temp);
    n = strtol(temp.c_str(),NULL, 10);

    // Allocate memory for y:
    y = new double [n+1];

    while (getline(ifile, temp) && counter<=n ){
      y[counter] = strtod(temp.c_str(),NULL);
    }
    
    // Close file stream:
    ifile.close();
  }

  solve_moments();
}

// Second type of Constructor:
CubicSplineProblem::CubicSplineProblem(double (*f) (double x), double start, double end, int num_points){
  a = start;
  b = end;
  n = num_points;

  // Initialize y:
  y = new double [n+1];

  for(int i=0; i<=n; i++){
    y[i] = (*f)(a + i*(b-a)/double(n));
  }

  solve_moments();
}

CubicSplineProblem::~CubicSplineProblem(void) {
  // Delete the pointer to interpolating points
  delete [] y;
  delete [] moms;
}

//-----------------------------------------------------

// Print problem:
void CubicSplineProblem::print(){
  cout << "The problem is defined on the interval [" << a << ", " << b << "]" << endl;
  cout << "with " << n+1 << " points." << endl;
  cout << "The cubic splines should interpolate at the following values: " << endl;

  for(int i=0; i<=n; i++){
    cout << y[i] << endl;
  }
}

// Solve to get moments
void CubicSplineProblem::solve_moments(){
  if(!moms){
  moms = new double[n+1];
  }
  // Set step size:
  double h=y[1]-y[0];

  double* sub;
  double* sup;
  double* diag;

  sub = new double [n-2];
  sup = new double [n-2];
  diag = new double[n-1];

  // Initialize sup and sup: 
  for(int i=0; i<n-2; i++){
    sub[i] = 1.0;
    sup[i] = 1.0;
  }
  // Initialize diags and moms;
  moms[0] = 0.;
  moms[n] = 0.;

  for(int i=0; i<n-1; i++){
    diag[i] = 4.0;
    moms[i+1] = 6./(h*h)*(y[i+2]-2*y[i+1]+y[i]);
  }

  // Initialize tridiagonal matrix
  TriDiagMat trid(diag, sub, sup, n-1);
  trid.trisolve(moms+1);  // +1 to increment to start at moms[1].
  
  delete [] sub;
  delete [] sup;
  delete [] diag;
}
