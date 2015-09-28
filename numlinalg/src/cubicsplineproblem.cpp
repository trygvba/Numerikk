//: cubicsplineproblem.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "cubicsplineproblem.h"

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
}

CubicSplineProblem::~CubicSplineProblem(void) {
  // Delete the pointer to interpolating points
  delete [] y;
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
