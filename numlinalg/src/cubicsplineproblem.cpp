//: cubicsplineproblem.cpp
#include <iostream>
#include <fstream>
#include <string>
#include "cubicsplineproblem.h"

using namespace std;

CubicSplineProblem::CubibSplineProblem(string filename){
  ifstream ifile (filename);
  string temp;  
  int counter=0;
  if (ifile.is_open()){
    // Get interval start
    getline(ifile, temp);
    a = stod(temp);

    // Get interval end
    getline(ifile, temp);
    b = stod(temp);

    // Get number of points
    getline(ifile, temp);
    n = stoi(temp);

    // Allocate memory for y:
    y = new double [n+1];

    while (getline(ifile, temp) && counter<=n ){
      y[counter] = stod(temp);
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
    y[i] = (*f)(a + i*(b-a));
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
  cout << "with " << n+1 << "points." << endl;
  cout << "The cubic splines should interpolate at the following values: " << endl;

  for(int i=0; i<=n; i++){
    cout << y[i] << endl;
  }
}
