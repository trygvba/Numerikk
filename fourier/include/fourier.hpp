// File: fourier.hpp
#ifndef FOURIER_HPP
#define FOURIER_HPP

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
        int get_Ncoeffs();
        double get_eval(const int i);
        void get_fourier_coefficient(const int i, double out[2]);

        // Using FFTW to update evaluations or coefficents:
        void update_coefficients_from_evals();
        void update_evals_from_coefficients();

        // Setter functions:
        void set_evals(double* in_eval, int in_N);
    private:
        int N;
        double* evals;      // Periodic evaluations
        double* fcoeffs;    // Fourier coefficients
        bool owns_evals;    // Ownership flag for evaluations
};

#endif // FOURIER_HPP
