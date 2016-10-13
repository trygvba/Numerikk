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

    // Scale Fourier coefficients:
    for (int i=0; i<2*(N/2+1); i++){
        fcoeffs[i] = fcoeffs[i]/((double) N);
    }
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

void FourierFunction::get_evals(double* output, int output_N){
    for (int i=0; i<N; i++){
        output[i] = evals[i];
    }
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
    // Scale Fourier coefficients:
    for (int i=0; i<2*(N/2+1); i++){
        fcoeffs[i] = fcoeffs[i]/((double) N);
    }
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

void FourierFunction::scale_coefficient(const int i, const double c_scale[2]){
    // Get current coefficient:
    double* c = &(fcoeffs[2*i]);
    // Scale using complex multiplication:
    double temp = c[0];
    c[0] = c[0]*c_scale[0] - c[1]*c_scale[1];
    c[1] = temp*c_scale[1] + c[1]*c_scale[0];
}

/*******************************************
 *          SMOOTHERS:
 *******************************************/
void fejer_smoothing(FourierFunction& f){
    // Declare variables:
    int Ncoeffs;
    double c[2];
    // Imaginary part of scaling is always 0.
    c[1] = 0.;
    // Get number of coefficients:
    Ncoeffs = f.get_Ncoeffs();

    // Go through each coefficient:
    for (int i=0; i<Ncoeffs; i++){
        c[0] = 1. - ( (double) i )/Ncoeffs;
        // Scale by c:
        f.scale_coefficient(i, c);
    }
    
}
