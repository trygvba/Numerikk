// File: polynomial.hpp
#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP


#include <iostream>
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
        void get_all_coeffs(double *output, int output_N) const;
        void set_coefficient(const int i, double val);
        void set_coeffs(double* c, int p);
        double eval(double x) const;
        double eval_diff(double x, int n) const;
        double get_zero(double init_x, double tol=1e-4, int max_iter = 1000) const;

        void set_ownership(bool own_flag);
        
    /******************
     *  OPERATORS:
     ******************/
        Polynomial1D operator+(const Polynomial1D& other);
        Polynomial1D operator-(const Polynomial1D& other);
        Polynomial1D& operator=(const Polynomial1D& other);
        void operator+=(const Polynomial1D& other);
        // Incremental scaler:
        void operator*=(double a);
        // Incremental subtractor:
        void operator-=(const Polynomial1D& other);

    private:
        double* coeffs;
        int deg;
        bool owns;
        
};

/********************************************
 *          OPERATORS:
 ********************************************/
std::ostream& operator<<(std::ostream& os, const Polynomial1D& poly);
/********************************************
 *  GENERATE DIFFERENT TYPES OF POLYNOMIALS:
 ********************************************/
Polynomial1D generate_chebyshev_polynomial(int n);
#endif // POLYNOMIAL_HPP
