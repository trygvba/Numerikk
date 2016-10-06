// File: polynomials.cpp

#include <cmath>
#include <iostream>
#include "polynomial.hpp"

using namespace std;
/*********************************
 *  Functions for Polynomial1D:
 *********************************/
Polynomial1D::Polynomial1D(double* c, int p){
    coeffs = c;
    deg = p;
    owns = false;
}

// Default constructor:
Polynomial1D::Polynomial1D(){
    coeffs = NULL;
    deg = 0;
    owns = false;
}
// Destructor:
Polynomial1D::~Polynomial1D(){
    if (owns){
        delete [] coeffs;
    }
}

// Get degree:
int Polynomial1D::get_deg(){
    return deg;
}

// Get coefficient:
double Polynomial1D::get_coeff(const int i){
    if (i<0 || i >= deg){
        cout << "Coefficient index was not valid." << endl;
        return 0.;
    }
    return coeffs[i];
}

// Set coefficients:
void Polynomial1D::set_coeffs(double* c, int p){
    coeffs = c;
    deg = p;
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

// Evaluate n'th derivative of Polynomial:
double Polynomial1D::eval_diff(double x, int n){
    if (n<0 || n >= get_deg()){
        return 0.;
    }
    else{
        double res = 0.0;
        double term;
        int i,j;
        for(i=n; i<get_deg(); i++){
            term = get_coeff(i)*pow(x,i-n);
            for (j=0; j<n; j++){
                term *= (i-j);
            }
            res += term;   
        }
        return res;
    }
    
}

/* Set ownership */
void Polynomial1D::set_ownership(bool own_flag){
    owns = own_flag;
}

/* Calculate zero of polynomial using Newton's method: */
double Polynomial1D::get_zero(double init_x, double tol, int max_iter){
    // Declare variables:
    double x = init_x;
    double px, px0, dpx;
    int counter = 0;

    // Initialize values:
    px = eval(x);
    px0 = px;

    while (abs(px/px0) >= tol && counter < max_iter){
        px = eval(x);
        dpx = eval_diff(x,1);
        x = x - px/dpx;
    }
    return x;
}
