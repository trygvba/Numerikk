// Class for the Cubic Spline Problem
#ifndef CUBICSPLINEPROBLEM_H
#define CUBICSPLINEPROBLEM_H

#include <string>
#include "tridiag.h"

class CubicSplineProblem {
  public:
    CubicSplineProblem(std::string filename);  // Constructor
    CubicSplineProblem(double (*f) (double x), double a, double b, int n); // Second type of constructor
    ~CubicSplineProblem();                     // Destructor

    void print();      // Print problem
    void solve_moments(); // Solve to get moments.
  private:
    double a;          // interval start
    double b;          // interval end
    int n;             // number of interpolating points
    double* y;         // interpolating values
    double* moms;      // moments
};

#endif // CUBICSPLINEPROBLEM_H
