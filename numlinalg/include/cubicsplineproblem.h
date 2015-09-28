// Class for the Cubic Spline Problem
#ifndef CUBICSPLINEPROBLEM_H
#define CUBICSPLINEPROBLEM_H

#include <string>

class CubicSplineProblem {
  public:
    CubicSplineProblem(string filename);  // Constructor
    CubicSplineProblem(double (*f) (double x), double a, double b, int n); // Second type of constructor
    ~CubicSplineProblem();                // Destructor

    void print();      // Print problem
  private:
    double a;          // interval start
    double b;          // interval end
    int n;             // number of interpolating points
    double* y;         // interpolating values
};

#endif // CUBICSPLINEPROBLEM_H
