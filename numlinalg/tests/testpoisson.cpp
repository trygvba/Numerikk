//: testpoisson.cpp

#include <cmath>
#include <iostream>
#include "poisson1d.h"
#include "plotter.h"

using namespace std;

// Test source:
double f(double x){
  return 1.;
}


int main(){

  int num_points = 100;

  //Poisson1D testprob("../inputfiles/testspline.txt");
  Poisson1D testprob(&f, 0., 1., num_points);
  testprob.print();
  
  testprob.solve();
  
  double* x = testprob.get_x();
  double* u = testprob.get_u();

  //Set up for plotting:
  Plotter fig;
  fig.plot_line(x, u, testprob.get_num_subints()+1);

  delete [] x;
  delete [] u;
}
