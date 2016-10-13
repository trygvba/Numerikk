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
        FourierFunction(const FourierFunction& f);
        ~FourierFunction();

        // Getter functions:
        int get_N() const;
        int get_Ncoeffs() const;
        double get_eval(const int i) const;
        void get_evals(double* output, int output_N) const;
        bool get_updated_status() const;
        void get_fourier_coefficient(const int i, double out[2]) const;

        // Using FFTW to update evaluations or coefficents:
        void update_coefficients_from_evals();
        void update_evals_from_coefficients();

        // Setter functions:
        void set_evals(double* in_eval, int in_N);

        /* Scale coefficient number i by a complex number
         * given by c_scale.
         */
        void scale_coefficient(const int i, const double c_scale[2]);
    private:
        int N;
        double* evals;      // Periodic evaluations
        double* fcoeffs;    // Fourier coefficients
        bool owns_evals;    // Ownership flag for evaluations
        bool updated;       // Evals and fcoeffs represent the same underlying function.
};

/************************
 *      OPERATORS:
 ************************/


/************************
 *      SMOOTHERS:
 ************************/
void fejer_smoothing(FourierFunction& f);
#endif // FOURIER_HPP
