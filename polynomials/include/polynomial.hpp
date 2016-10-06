// File: polynomial.hpp
#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP


#include <vector>
/**************************************
 *      1D Polynomial class
 **************************************/
class Polynomial1D {
    public:
        Polynomial1D(double* c, int p);
        Polynomial1D();
        ~Polynomial1D();

        int get_deg();
        double get_coeff(const int i);
        void set_coeffs(double* c, int p);
        double eval(double x);
        double eval_diff(double x, int n);
        double get_zero(double init_x, double tol=1e-4, int max_iter = 1000);

        void set_ownership(bool own_flag);
        
    private:
        double* coeffs;
        int deg;
        bool owns;
        
};

#endif // POLYNOMIAL_HPP
