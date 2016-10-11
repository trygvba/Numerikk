// File: fourier.cpp

#include "fourier.hpp"
#include "fftw3.h"
#include <cmath>
#include <iostream>
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
    owns_evals = false;

    // Allocate memory for fcoeffs:
    fcoeffs = new double[2*(N/2+1)];
    // Set up for FFT:
    fftw_plan p;
    p = fftw_plan_dft_r2c_1d(N, evals, (fftw_complex*) fcoeffs,
                            FFTW_ESTIMATE);
    
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

int FourierFunction::get_Ncoeffs(){
    return N/2+1;
}

double FourierFunction::get_eval(const int i){
    return evals[i];
}

void FourierFunction::get_fourier_coefficient(const int i, double out[2]){
    out[0] = fcoeffs[2*i];
    out[1] = fcoeffs[2*i+1];
}

/******************************************
 *      UPDATE COEFFICIENTS OR EVALS:
 ******************************************/
void FourierFunction::update_coefficients_from_evals(){
    // Set up for FFT:
    fftw_plan p;
    p = fftw_plan_dft_r2c_1d(N, evals, (fftw_complex*) fcoeffs,
                             FFTW_ESTIMATE);

    // Execute FFT:
    fftw_execute(p);
    // Destroy plan:
    fftw_destroy_plan(p);
}


void FourierFunction::update_evals_from_coefficients(){
    // Set up for FFT:
    fftw_plan p;
    p = fftw_plan_dft_c2r_1d(N, (fftw_complex*) fcoeffs, evals,
                             FFTW_ESTIMATE);

    // Execute FFT:
    fftw_execute(p);
    // Destroy plan:
    fftw_destroy_plan(p);
    // Scale as N:
    for (int i=0; i<N; i++){
        evals[i] *= 1./( (double) N);
    }
}

/************************************************
 *      SETTER FUNCTIONS:
 ************************************************/
void FourierFunction::set_evals(double* in_eval, int in_N){
    // Clear data, if necessary:
    if (owns_evals && evals){
        delete [] evals;
    }
    if (fcoeffs && in_N != N){
        delete [] fcoeffs;
        N = in_N;
        fcoeffs = new double[2*(N/2+1)];
    }
    else if (!fcoeffs){
        N = in_N;
        fcoeffs = new double[2*(N/2+1)];
    }
    evals = in_eval;
    owns_evals = false;
    // Set up for FFT:
    fftw_plan p;
    p = fftw_plan_dft_r2c_1d(N, evals, (fftw_complex*) fcoeffs,
                             FFTW_ESTIMATE);
    // Execute FFT:
    fftw_execute(p);
    // Destroy plan:
    fftw_destroy_plan(p);
}
