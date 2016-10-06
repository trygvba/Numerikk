// File: fourier.hpp
#ifndef FOURIER_HPP
#define FOURIER_HPP

#include <fftw3.h>
/************************************
 *      FOURIER CLASS:
 ************************************/
class FourierFunction {
    public:
        FourierFunction();
        FourierFunction(double* in_eval, int in_N);
        ~FourierFunction();

        // Getter functions:
        int get_N();
        double get_eval(const int i);
        void get_fourier_coefficient(const int i, double* out);
    private:
        int N;
        double* evals;      // Periodic evaluations
        (fftw_complex*) fcoeffs;    // Fourier coefficients
        bool owns_evals;    // Ownership flag for evaluations
};

#endif // FOURIER_HPP
