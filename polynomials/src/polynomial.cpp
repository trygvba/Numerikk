// File: polynomials.cpp

#include <cmath>
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

// Copy constructor:
Polynomial1D::Polynomial1D(const Polynomial1D& poly){
    // Get polynomial degree:
    deg = poly.get_deg();
    // Allocate memory for coefficients:
    coeffs = new double[deg];
    // Go through each coefficient:
    for (int i=0; i<deg; i++){
        coeffs[i] = poly.get_coeff(i);
    }
    // Set ownership:
    set_ownership(true);
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
int Polynomial1D::get_deg() const {
    return deg;
}

// Get coefficient:
double Polynomial1D::get_coeff(const int i) const{
    if (i<0 || i >= deg){
        cout << "Coefficient index was not valid." << endl;
        return 0.;
    }
    return coeffs[i];
}

void Polynomial1D::get_all_coeffs(double *output, int output_N) const{
    for (int i=0; i<get_deg(); i++){
        output[i] = coeffs[i];
    }
}

void Polynomial1D::set_coefficient(const int i, double val){
    // Check that index is OK:
    if (i<0 || i >= get_deg()){
        throw "Input index to Polynomial1D::set_coefficient was invalid.";
    }
    // Set coefficient:
    coeffs[i] = val;
}
// Set coefficients:
void Polynomial1D::set_coeffs(double* c, int p){
    coeffs = c;
    deg = p;
}

// Evaluate polynomial:
double Polynomial1D::eval(double x) const{
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
double Polynomial1D::eval_diff(double x, int n) const{
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
double Polynomial1D::get_zero(double init_x, double tol, int max_iter) const{
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

/*********************************
 *      OPERATORS:
 *********************************/
Polynomial1D Polynomial1D::operator+(const Polynomial1D& other){
    // Declare variables:
    int maxN;
    const Polynomial1D* polyp;
    Polynomial1D result;

    // First, let's get the minimum and max degree polys:
    maxN = max(other.get_deg(), this->get_deg());
    cout << "maxN is " << maxN << endl;
    // Copy the polynomial of greatest degree and point to the other:
    if (this->get_deg() == maxN){
        result = *this;
        polyp = &other;
    }
    else {
        cout << "Other had greatest degree." << endl;
        result = other;
        polyp = this;
    }
    // Go through each coefficient:
    for (int i=0; i<polyp->get_deg(); i++){
        result.set_coefficient(i, result.get_coeff(i) + polyp->get_coeff(i));
    }
    return result;
}

Polynomial1D Polynomial1D::operator-(const Polynomial1D& other){
    // Declare variables:
    int maxN;
    const Polynomial1D* polyp;
    Polynomial1D result;

    // First, let's get the minimum and max degree polys:
    maxN = max(other.get_deg(), this->get_deg());
    cout << "maxN is " << maxN << endl;
    // Copy the polynomial of greatest degree and point to the other:
    if (this->get_deg() == maxN){
        result = *this;
        polyp = &other;
    }
    else {
        cout << "Other had greatest degree." << endl;
        result = other;
        polyp = this;
    }
    // Go through each coefficient:
    for (int i=0; i<polyp->get_deg(); i++){
        result.set_coefficient(i, result.get_coeff(i) - polyp->get_coeff(i));
    }
    return result;

}

Polynomial1D& Polynomial1D::operator=(const Polynomial1D& other){
    if (this != &other){
        // Delete coeffs if this owns:
        if (owns){
            delete [] coeffs;
        }
        deg = other.get_deg();
        // allocate new memory:
        coeffs = new double[deg];
        // Go through each coefficient and copy:
        for (int i=0; i<deg; i++){
            coeffs[i] = other.get_coeff(i);
        }
        owns = true;
    }
    return *this;
}

void Polynomial1D::operator+=(const Polynomial1D& other){
    // If degree is lower than what we already have:
    if (other.get_deg() > this->get_deg()){
        // Set new array for coefficients:
        double* c = new double[other.get_deg()];
        for (int i=0; i<this->get_deg(); i++){
            c[i] = this->get_coeff(i) + other.get_coeff(i);
        }
        for (int i=this->get_deg(); i<other.get_deg(); i++){
            c[i] = other.get_coeff(i);
        }
        // Set new coefficients:
        this->set_coeffs(c, other.get_deg());
        this->set_ownership(true);

    }
    else {
        for (int i=0; i<other.get_deg(); i++){
            this->set_coefficient(i, this->get_coeff(i) + other.get_coeff(i));
        }
    }
}

void Polynomial1D::operator*=(double a){
    for (int i=0; i<get_deg(); i++){
        set_coefficient(i, get_coeff(i)*a);
    }
}

void Polynomial1D::operator-=(const Polynomial1D& other){
    // If degree is lower than what we already have:
    if (other.get_deg() > this->get_deg()){
        // Set new array for coefficients:
        double* c = new double[other.get_deg()];
        for (int i=0; i<this->get_deg(); i++){
            c[i] = this->get_coeff(i) - other.get_coeff(i);
        }
        for (int i=this->get_deg(); i<other.get_deg(); i++){
            c[i] = -other.get_coeff(i);
        }
        // Set new coefficients:
        this->set_coeffs(c, other.get_deg());
        this->set_ownership(true);

    }
    else {
        for (int i=0; i<other.get_deg(); i++){
            this->set_coefficient(i, this->get_coeff(i) - other.get_coeff(i));
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Polynomial1D& poly){
    os << "An instance of Polynomial1D at " << &poly;
    return os;
}
/*************************************************************
 *      GENERATE POLYNOMIALS:
 *************************************************************/
Polynomial1D generate_chebyshev_polynomial(int n){
    //Declare variables:
    double* prev;
    double* current;
    double* tmpswp;
    Polynomial1D result;

    // Check input:
    if (n<0){
        throw "Input n to generate Chebyshev polynomial should be a nonnegative integer.";
    }
    // Allocate memory:
    if (n==0){
        result = Polynomial1D();
    }
    else if (n==1){
        current = new double[2];
        current[0] = 0.;
        current[1] = 1.;
        result.set_coeffs(current, 2);
        result.set_ownership(true);
    }
    else {
        prev = new double[n+1];
        current = new double[n+1];
        prev[0] = 1.;
        current[0] = 0.;
        current[1] = 1.;
        for (int d=1; d<n; d++){
            // Swap pointers:
            tmpswp = current;
            current = prev;
            prev = tmpswp;
            //Update current
            for (int k=0; k<=d-1; k++){
                current[k] = -current[k];
            }
            current[d] = 0.;
            current[d+1] = 0.;
            for (int k=d; k>=0; k--){
                current[k+1] += 2.*prev[k];
            }
        }
        // Delete previous:
        delete [] prev;
        // Set coefficients for result:
        result.set_coeffs(current, n+1);
        result.set_ownership(true);   
    }
    return result;
}
