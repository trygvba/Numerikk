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
    updated = true;
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
    updated = true;
}

FourierFunction::FourierFunction(const FourierFunction& f){
    // Declare variables:
    double *temp;
    // Set everything equal:
    N = f.get_N();
    // Need to allocate for both evals and fcoeffs:
    evals = new double[N];
    fcoeffs = new double[2*(N/2+1)];
    owns_evals = true;

    // Copy fourier coefficients:
    for (int i=0; i<(N/2+1); i++){
        temp = &(fcoeffs[2*i]);
        f.get_fourier_coefficient(i, temp);
    }
    updated = false;
    // Update evaluations accordingly:
    this->update_evals_from_coefficients();
}

FourierFunction::~FourierFunction(){
    if (owns_evals && evals){
        delete [] evals;
    }
    if (fcoeffs){
        delete [] fcoeffs;
    }
}

int FourierFunction::get_N() const {
    return N;
}

int FourierFunction::get_Ncoeffs() const {
    return N/2+1;
}

double FourierFunction::get_eval(const int i) const {
    return evals[i];
}

void FourierFunction::get_evals(double* output, int output_N) const {
    for (int i=0; i<N; i++){
        output[i] = evals[i];
    }
}
void FourierFunction::get_fourier_coefficient(const int i, double out[2]) const {
    out[0] = fcoeffs[2*i];
    out[1] = fcoeffs[2*i+1];
}

bool FourierFunction::get_updated_status() const {
    return updated;
}
/******************************************
 *      UPDATE COEFFICIENTS OR EVALS:
 ******************************************/
void FourierFunction::update_coefficients_from_evals(){
    // Set up for FFT:
    fftw_plan p;
    // If not already updated:
    if (!updated){
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
        updated = true;
    }
}


void FourierFunction::update_evals_from_coefficients(){
    // Set up for FFT:
    fftw_plan p;
    // Update if necessary:
    if (!updated){
        // DFT C2R destroys input by default. Needs additional flag.
        p = fftw_plan_dft_c2r_1d(N, (fftw_complex*) fcoeffs, evals,
                             FFTW_ESTIMATE|FFTW_PRESERVE_INPUT);

        // Execute FFT:
        fftw_execute(p);
        // Destroy plan:
        fftw_destroy_plan(p);
        updated = true;
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
    updated = true;
}

void FourierFunction::scale_coefficient(const int i, const double c_scale[2]){
    // Get current coefficient:
    double* c = &(fcoeffs[2*i]);
    // Scale using complex multiplication:
    double temp = c[0];
    c[0] = c[0]*c_scale[0] - c[1]*c_scale[1];
    c[1] = temp*c_scale[1] + c[1]*c_scale[0];

    if (updated)
        updated = false;
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
