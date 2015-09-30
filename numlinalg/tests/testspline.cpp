//: testspline.cpp

#include <cmath>
#include <iostream>
#include "cubicsplineproblem.h"

using namespace std;

//Test function:
double f(double x){
  return atan(x);
}

int main(){
  double a = 0.;
  double b = 4.;
  
  int num_points = 4;

  CubicSplineProblem testprob(&f, a, b, num_points);

  testprob.print();
  
  cout << endl;
  
  testprob.print_coeffs();

  return 0;
}
