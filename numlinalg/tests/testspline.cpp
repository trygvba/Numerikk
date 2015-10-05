//: testspline.cpp

#include <cmath>
#include <iostream>
#include "cubicsplineproblem.h"
#include "plotter.h"

using namespace std;

//Test function:
double f(double x){
  return atan(x);
}

int main(){
  /*
  double a = -1.;
  double b = 1.;
  
  int num_points = 14;
  */
  //CubicSplineProblem testprob(&f, a, b, num_points);
  CubicSplineProblem testprob("../inputfiles/testspline.txt");

  testprob.print();
  
  cout << endl;
  
  testprob.print_coeffs();
  /*-------------------------------
 *      TRY THE PLOTTER
 *--------------------------------*/
  int num_points = 100;
  double *x;
  double *y;

  x = new double[num_points];
  y = new double[num_points];
  
  // Set x:
  for(int i=0; i<num_points; i++){
    x[i] =testprob.get_intstart()+ i/double(num_points-1)*(testprob.get_intend()-testprob.get_intstart());
  }
  testprob.eval_spline(x, y, num_points);
 
  // Set up for plotting.
  Plotter fig;
  fig.plot_line(x,y, num_points);

  delete [] x;
  delete [] y;

  return 0;
}
