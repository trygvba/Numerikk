// File: polynomial.hpp
#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP


/**************************************
 *      1D Polynomial class
 **************************************/
class Polynomial1D {
    public:
        Polynomial1D(double* c, int p);
        Polynomial1D();
        ~Polynomial1D();

        int get_deg();
        double get_coeff(int i);
        void set_coeffs(double* c, int p);

    private:
        double* coeffs;
        int deg;
};
#endif // POLYNOMIAL_HPP
