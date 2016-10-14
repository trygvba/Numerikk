//File: flux_function.hpp
#ifndef FLUX_FUNCTION_HPP
#define FLUX_FUNCTION_HPP

#include <iostream>
/**********************************
 *  ABSTRACT FLUX FUNCTION CLASS:
 **********************************/
class FluxFunctionBase{
    public:
        virtual ~FluxFunctionBase(){}
        FluxFunctionBase(){}
        // Only thing we need thus far is an evaluate function:
        virtual double evaluate(double u) const = 0;
};
/**********************************
 *  POWER BASE FLUX FUNCTION:
 **********************************/
class FluxFunctionPower: public FluxFunctionBase {
    public:
        FluxFunctionPower(): n(0) {}
        FluxFunctionPower(int n_): n(n_) {} 
        ~FluxFunctionPower();
    /* Virtual functions: */
        double evaluate(double u) const;
    
    /* Getter functions: */
        int get_n() const;
        
    private:
        int n;      // Power of flux function 
};

/* Operators */
std::ostream & operator << ( std::ostream& os, const FluxFunctionPower& f);
#endif // FLUX_FUNCTION_HPP
