// File: fourier.cpp

#include "fourier.hpp"
#include "fftw3.h"
#include <cmath>
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


void FourierFunction::set_eval(const int i, double val){
    evals[i] = val;
    if (updated){
        updated = false;
    }
}

void FourierFunction::set_coefficient(const int i, double cval[2]){
    // Update coefficient:
    fcoeffs[2*i] = cval[0];
    fcoeffs[2*i+1] = cval[1];

    if (updated)
        updated = false;
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
 *      OVERLOADED OPERATORS:
 *******************************************/
FourierFunction FourierFunction::operator+(const FourierFunction& other){
    // Check that lengths are equal:
    if (other.get_N() != this->get_N()){
        throw "Summand FourierFunctions did not have same length N.";
    }
    // Declare result instance:
    FourierFunction result(other);
    double temp1[2];
    double temp2[2];
    // Run through each eval:
    for (int i=0; i<other.get_Ncoeffs(); i++){
        result.get_fourier_coefficient(i, temp1);
        this->get_fourier_coefficient(i, temp2);
        temp1[0] += temp2[0];
        temp1[1] += temp2[1];
        result.set_coefficient(i, temp1);
    }
    // Not updated:
    if (updated)
        updated = false;
    return result;
}

FourierFunction& FourierFunction::operator=(const FourierFunction& other){
    if (this != &other){
        // Declare variables:
        double *temp;
        // Set everything equal:
        N = other.get_N();
        // Need to allocate for both evals and fcoeffs:
        if (evals && owns_evals){
            delete [] evals;
        }
        if (fcoeffs){
            delete [] fcoeffs;
        }
        evals = new double[N];
        fcoeffs = new double[2*(N/2+1)];
        owns_evals = true;

        // Copy fourier coefficients:
        for (int i=0; i<(N/2+1); i++){
            temp = &(fcoeffs[2*i]);
            other.get_fourier_coefficient(i, temp);
        }
        updated = false;
        // Update evaluations accordingly:
        this->update_evals_from_coefficients();
    }
    return *this;
}

void FourierFunction::operator+=(const FourierFunction& other){
    // Check that input has appropriate length:
    if (other.get_N() != N){
        throw "Input to += operator did not have same length as lvalue.";
    }
    // Add Fourier coefficients:
    double temp1[2];
    double temp2[2];
    for (int i=0; i<get_Ncoeffs(); i++){
        // Set new coefficient:
        this->get_fourier_coefficient(i, temp1);
        other.get_fourier_coefficient(i, temp2);
        temp1[0] += temp2[0];
        temp1[1] += temp2[1];
        
        this->set_coefficient(i, temp1);
    }
    // Set updated:
    updated = false;
}

void FourierFunction::operator*=(double a){
    double temp[2];
    for (int i=0; i<get_Ncoeffs(); i++){
        this->get_fourier_coefficient(i, temp);
        temp[0] *= a;
        temp[1] *= a;
        this->set_coefficient(i, temp);
    }
    // Set updated:
    updated = false;
}

void FourierFunction::operator-=(const FourierFunction& other){
    //Check that input has appropriate length:
    if (other.get_N() != N){
        throw "Input to -= operator do not have some length as lvalue.";
    }
    // Subtract Fourier coefficients:
    double temp1[2];
    double temp2[2];
    for (int i=0; i<get_Ncoeffs(); i++){
        // Set new coefficients:
        this->get_fourier_coefficient(i, temp1);
        other.get_fourier_coefficient(i, temp2);
        temp1[0] -= temp2[0];
        temp1[1] -= temp2[1];
        this->set_coefficient(i, temp1);
    }
    // Set updated:
    updated = false;
}

FourierFunction operator*(double a, const FourierFunction& rF){
    // Declare result:
    FourierFunction result(rF);

    // Scale each Coefficient:
    double temp[2];
    for (int i=0; i<result.get_Ncoeffs(); i++){
        result.get_fourier_coefficient(i, temp);
        temp[0] *= a;
        temp[1] *= a;
        result.set_coefficient(i, temp);
    }
    return result;
}

FourierFunction operator-(const FourierFunction& lval, const FourierFunction& rval){
    // Declare result:
    FourierFunction result(rval);
    // Scale it by -1.:
    result *= -1.;
    // Add lvalue to it:
    result += lval;
    // Return result:
    return result;
}
std::ostream & operator<< ( std::ostream& os, const FourierFunction& f){
    os << "Instance of FourierFunction with " << f.get_N() << " points at " << &f;
    return os;
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
