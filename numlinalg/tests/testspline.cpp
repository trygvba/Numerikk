//: testspline.cpp

#include <cmath>
#include <iostream>
#include "cubicsplineproblem.h"

using namespace std;

//Test function:
double f(double x){
  return atan(10*x);
}

int main(){
  double a = -1.;
  double b = 1.;
  
  int num_points = 14;

  CubicSplineProblem testprob(&f, a, b, num_points);

  testprob.print();

  return 0;
}
