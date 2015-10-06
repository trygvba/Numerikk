//: poisson1d.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include "poisson1d.h"
#include "tridiag.h"

using namespace std;

Poisson1D::Poisson1D(){
  // Do nothing
}

Poisson1D::Poisson1D(string filename){
  ifstream ifile;
  string temp;
  int counter = 0;

  ifile.open(filename.c_str());
  
  if(ifile.is_open()){
    // Get interval start
    getline(ifile, temp);
    a = atof(temp.c_str());

    // Get interval end
    getline(ifile, temp);
    b = atof(temp.c_str());

    // Get number of points
    getline(ifile,temp);
    n = atoi(temp.c_str());

    // Set x and h:
    h = (b-a)/double(n);

    x = new double[n+1];
    for(int i=0; i<n+1; i++){
      x[i] = a+i*h;
    }
    
    // Allocate memory for u (where loading will be):
    u = new double [n+1];

    while (!ifile.eof() && counter<=n) {
      getline(ifile, temp);
      u[counter] = h*h*atof(temp.c_str());
      if(ifile.fail()){
        cout << "Couldn't read double from file." << endl;
      }
      counter++;
    }
  
    // Close file stream
    ifile.close();

  }

}


// Second non-trivial constructor
Poisson1D::Poisson1D(double (*f)(double x), double start, double end, int num_points):
  a(start), b(end), n(num_points)
{
  // Get step length and points
  h = (b-a)/double(n);

  x = new double [n+1];
  u = new double [n+1];

  for(int i=0; i<=n; i++){
    x[i] = a+i*h;
    u[i] = (*f)(x[i])*h*h;
  }
}

Poisson1D::~Poisson1D(){
  if(u) delete [] u;
  if(x) delete [] x;
}

//----------------------------------------------------


// print problem
void Poisson1D::print(){
  cout << "The problem is defined in the interval [" << a << ", " << b << "]" << endl;
  cout << " with " << n+1 << " points." << endl;
  cout << "The 1D laplacian of the solution should be the following values: " << endl;
  
  for(int i=0; i<n+1; i++){
    cout << u[i] << endl;
  } 
  cout << endl;
}

double Poisson1D::get_intstart(){
  return a;
}

double Poisson1D::get_intend(){
  return b;
}

int Poisson1D::get_num_subints(){
  return n;
}

// Solve problem
void Poisson1D::solve(){
  
  double* sup;
  double* sub;
  double* diag;
  // Initialize the tridiagonal matrix
  sup = new double [n-2];
  sub = new double [n-2];
  diag = new double [n-1];

  for (int i=0; i<n-2; i++){
    sub[i] = -1.;
    sup[i] = -1.;
    diag[i] = 2.;
  } 
  diag[n-2] = 2;
  // Set boundary values;
  u[0] = 0.;
  u[n] = 0.;

  TriDiagMat trid(diag, sub, sup, n-1);
  trid.trisolve((u+1));

  // Clean up:
  delete [] sub;
  delete [] sup;
  delete [] diag;
}

double* Poisson1D::get_x(){
  double* res = new double [n+1];
  
  for(int i=0; i<n+1; i++){
    res[i] = x[i];
  }
  return res;
}

double* Poisson1D::get_u(){
  double* res = new double [n+1];

  for(int i=0; i<n+1; i++){
    res[i] = u[i];
  }
  return res;
}
