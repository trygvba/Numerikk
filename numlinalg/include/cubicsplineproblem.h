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
    void print_coeffs();  // Print coeffs.
    void solve_moments(); // Solve to get moments.
    void eval_coeffs();   // Evaluate coeffs
    int get_index(double x); // Get interval where x lies.
		double eval_at_point(double x);	// Evaluate the spline at a point.
		void eval_spline(double* x, double *y, int num_points); // Evaluate spline at several points.

		double get_intstart();
		double get_intend();
  private:
    double a;          // interval start
    double b;          // interval end
    int n;             // number of interpolating points
    double* y;         // interpolating values
    double* moms;      // moments

    double** coeffs;   // 2-dimensional array with coefficients.
};

#endif // CUBICSPLINEPROBLEM_H
