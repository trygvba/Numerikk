//File: flux_function.hpp
#include "flux_function.hpp"
#include <cmath>
/**********************************
 *  FLUX FUNCTION ABSTRACT BASE:
 **********************************/

/**********************************
 *   POWER BASE FLUX FUNCTION
 **********************************/
FluxFunctionPower::~FluxFunctionPower(){
}

double FluxFunctionPower::evaluate(double u) const{
    return pow(u,n); 
}

/* Getter functions: */
int FluxFunctionPower::get_n() const{
    return n;
}

/* Operators: */
std::ostream & operator << ( std::ostream& os, const FluxFunctionPower& f ){
    os << "Flux function u**" << f.get_n() << " at " << &f;
}
