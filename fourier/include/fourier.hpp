// File: fourier.hpp
#ifndef FOURIER_HPP
#define FOURIER_HPP

/************************************
 *      FOURIER CLASS:
 ************************************/
class FourierFunction {
    public:
        // Default constructor:
        FourierFunction();
        // Constructor taking in a raw pointer to the point evaluations:
        FourierFunction(double* in_eval, int in_N);
        // Copy constructor:
        FourierFunction(const FourierFunction& f);
        // Destructor:
        ~FourierFunction();

        // Getter functions:
        int get_N() const;          // Get number of evaluations
        int get_Ncoeffs() const;    // Get number of Fourier coefficients
        double get_eval(const int i) const; // Get i'th evaluation
        void get_evals(double* output, int output_N) const; // Get all evaluation copied to output pointer
        bool get_updated_status() const;                    // Get wether evaluations are updated to coefficients.
        void get_fourier_coefficient(const int i, double out[2]) const; // Get Fourier coefficient number i.

        // Using FFTW to update evaluations or coefficents:
        void update_coefficients_from_evals();              // Using current coefficients, update evaluations.
        void update_evals_from_coefficients();              // Using current evaluations, update coefficients.

        // Setter functions:
        void set_evals(double* in_eval, int in_N);          // Set new evaluations.

        /* Scale coefficient number i by a complex number
         * given by c_scale.
         */
        void scale_coefficient(const int i, const double c_scale[2]);       // Scale the i'th Fourier coefficient by complex number c_scale

    /********************************
     *      OPERATORS:
     ********************************/
    /********************************
     *  PRIVATE MEMBER VARIABLES:
     ********************************/
    private:
        int N;              // Number of points
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
