// File: conservationlaw.hpp
#ifndef CONSERVATION_LAW_HPP
#define CONSERVATION_LAW_HPP

#include "fourier.hpp"
/*****************************
 *  CONSERVATION LAW:
 *****************************/
// Typedef for Flux function:
//      flux function f(u)
typedef double (*fluxfunction)(double);
class ConservationLaw {
    public:

    private:
        double T;             // End time;
        FourierFunction& u0;  // Initial value
        flux F;               // Flux function.
};
#endif //CONSERVATION_LAW_HPP
