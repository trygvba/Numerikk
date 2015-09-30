//: cubicsplineproblem.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include "cubicsplineproblem.h"
#include "tridiag.h"

using namespace std;

CubicSplineProblem::CubicSplineProblem(string filename){
  ifstream ifile;
  string temp;  
  int counter=0;

  ifile.open(filename.c_str());
//  ifile.open(filename.c_str());
  if (ifile.is_open()){
    // Get interval start
    getline(ifile, temp);
    a = atof(temp.c_str());

    // Get interval end
    getline(ifile, temp);
    b = atof(temp.c_str());

    // Get number of points
    getline(ifile, temp);
    n = atoi(temp.c_str());

    // Allocate memory for y:
    y = new double [n+1];

    while (!ifile.eof() && counter<=n ){
      getline(ifile, temp);
      y[counter] = atof(temp.c_str());
      if(ifile.fail()){
        cout << "Couldn't read a double from file." << endl;
      }
      counter++;
    }
    
    
    // Close file stream:
    ifile.close();
  }

  coeffs = NULL;
  moms = NULL;
  // get moments and coeffs
  solve_moments();
  eval_coeffs();
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
  
  coeffs = NULL;
  moms = NULL;

  solve_moments();
  eval_coeffs();
}

CubicSplineProblem::~CubicSplineProblem(void) {
  // Delete the pointer to interpolating points
  if(y) delete [] y;
  if(moms) delete [] moms;
  
  if(coeffs){
    for(int i=0; i<n; i++){
      delete [] coeffs[i];
    }
    delete [] coeffs; 
  }
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

// Print coefficients:
void CubicSplineProblem::print_coeffs(){
  cout << "The coefficients for the piecewise polynomials are: " << endl;
  for(int i=0; i<n; i++){
    cout << coeffs[i][0] << " ";
    cout << coeffs[i][1] << " ";
    cout << coeffs[i][2] << " ";
    cout << coeffs[i][3] << endl;
  }
}

// Solve to get moments
void CubicSplineProblem::solve_moments(){
  if(!moms){
    moms = new double[n+1];
  }
  // Set step size:
  double h=(b-a)/double(n);

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
  trid.trisolve((moms+1));  // +1 to increment to start at moms[1].
  
  delete [] sub;
  delete [] sup;
  delete [] diag;
}

// Evaluate the coefficients, when given moments:
void CubicSplineProblem::eval_coeffs(){
  
  // There are n polynomials in the partition  
  coeffs = new double*[n];

  // Step size
  double h = (b-a)/double(n);

  // Go through each polynomial
  for(int i=0; i<n; i++){
    coeffs[i] = new double[4];
    
    coeffs[i][0] = y[i];
    coeffs[i][1] = (y[i+1] - y[i])/h - h/3.*moms[i]-h/6.*moms[i+1];
    coeffs[i][2] = 0.5*moms[i];
    coeffs[i][3] = (moms[i+1]-moms[i])/(6.*h);
  }

}
