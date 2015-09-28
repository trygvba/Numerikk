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


CubicSplineProblem::~CubicSplineProblem(void) {
  // Delete the pointer to interpolating points
  delete [] y;
}
