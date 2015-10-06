// Class for 2-point boundary value problem
#ifndef POISSON1D_H
#define POISSON1D_H

#include <string>

class Poisson1D: {
  public:
    Poisson1D(std::string filename);
    Poisson1D(double (*f) (double x), double a, double b, int n);
    ~Poisson1D();

    void print();     // Print problem
    
  private:
    double a;         // Interval start
    double b;         // interval end
    double h;         // step length
    int n;            // number of subintervals
    double *u;        // approximate solution at points.
    double *x;        // points
};

#endif // POISSON1D_H
