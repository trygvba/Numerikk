// Class for the Cubic Spline Problem
#ifndef CUBICSPLINEPROBLEM_H
#define CUBICSPLINEPROBLEM_H

#include <string>

class CubicSplineProblem {
  public:
    CubicSplineProblem(string filename);
  private:
    double a;          // interval start
    double b;          // interval end
    int n;             // number of interpolating points
    double* y;         // interpolating values
};

#endif // CUBICSPLINEPROBLEM_H
