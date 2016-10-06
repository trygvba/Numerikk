// File: fourier.cpp

#include "fourier.hpp"

/******************************
 *  FOURIER CLASS FUNCTIONS:
 ******************************/

FourierFunction::FourierFunction(){
    N = 0;
    evals = NULL;
    fcoeffs = NULL;
    owns_evals = false;
}

FourierFunction::FourierFunction(double* in_eval, int in_N){
    // Number of points is then N:
    N = in_N;
    evals = in_eval;

    // Allocate memory for fcoeffs:
    fcoeffs = new fftw_complex[(N/2+1)];
    // Set up for FFT:
    fftw_plan p;
    p = fftw_plan_dft_r2c_1d(N, evals, fcoeffs);
    
    // Execute FFT:
    fftw_execute(p);
    // Destroy plan:
    fftw_destroy_plan(p);
}

FourierFunction::~FourierFunction(){
    if (owns_evals && evals){
        delete [] evals;
    }
    if (fcoeffs){
        delete [] fcoeffs;
    }
}

int FourierFunction::get_N(){
    return N;
}

double FourierFunction::get_eval(const int i){
    return evals[i];
}

void FourierFunction::get_fourier_coefficient(const int i, double* out, int len){
    out[0] = fcoeffs[i][0];
    out[1] = fcoeffs[i][1];
}
