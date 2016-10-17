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
        // Copy constructor:
        Polynomial1D(const Polynomial1D& poly);
        // Default constructor:
        Polynomial1D();
        // Destructor:
        ~Polynomial1D();

        int get_deg() const;
        double get_coeff(const int i) const;
        void set_coeffs(double* c, int p);
        double eval(double x) const;
        double eval_diff(double x, int n) const;
        double get_zero(double init_x, double tol=1e-4, int max_iter = 1000) const;

        void set_ownership(bool own_flag);
        
    private:
        double* coeffs;
        int deg;
        bool owns;
        
};

/********************************************
 *  GENERATE DIFFERENT TYPES OF POLYNOMIALS:
 ********************************************/
Polynomial1D generate_chebyshev_polynomial(int n);
#endif // POLYNOMIAL_HPP
