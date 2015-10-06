//: poisson1d.cpp
#include <iostream>
#include <fstream>
#include <string>
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

    // Allocate memory for and u (where loading will be):
    u = new double [n+1];

    while (!ifile.eof() && counter<=n) {
      getline(ifile, temp);
      y[counter] = atof(temp.c_str());
      if(ifile.fail()){
        cout << "Couldn't read double from file." << endl;
      }
      counter++;
    }
  
    // Close file stream
    ifile.close();

  }

  // Set x and h:
  h = (b-a)/double(n);

  x = new double[n+1];
  for(int i=0; i<n+1; i++){
    x[i] = a+i*h;
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
    u[i] = (*f)(x[i]);
  }
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
