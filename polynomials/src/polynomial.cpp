// File: polynomials.cpp

#include <cmath>
#include <iostream>
#include "polynomial.hpp"

using namespace std;
/*********************************
 *  Functions for Polynomial1D:
 *********************************/
Polynomial1D::Polynomial1D(double* c, int p){
    if (c){
        coeffs = c;
        deg = p;
    }
    else {
        coeffs = NULL;
        deg = -1;
    }
}

// Default constructor:
Polynomial1D::Polynomial1D(){
    coeffs = NULL;
    deg = -1;
}
// Destructor:
Polynomial1D::~Polynomial1D(){
}

// Get degree:
int Polynomial1D::get_deg(){
    return deg;
}

// Get coefficient:
double Polynomial1D::get_coeff(int i){
    if (i<0 || i >= deg){
        cout << "Coefficient index was not valid." << endl;
        return 0.;
    }
    return coeffs[i];
}

// Set coefficients:
void Polynomial1D::set_coeffs(double* c, int p){
    if (c){
        coeffs = c;
        deg = p;
    }
    else {
        coeffs = NULL;
        deg = -1;
    }
}

// Evaluate polynomial:
double Polynomial1D::eval(double x){
    // Declare variable:
    double res = 0.0;

    // Go through each term:
    for (int i=0; i<get_deg(); i++){
        res += get_coeff(i)*pow(x,i);
    }

    // Return result:
    return res;
}
