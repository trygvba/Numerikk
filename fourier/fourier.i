%module fourier
%{
    #define SWIG_FILE_WITH_INIT
    #include "fourier.hpp"
%}

%include "numpy.i"
%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* in_eval, int in_N)};
%apply (double ARGOUT_ARRAY1[ANY]) { (double out[2]) };

%include "fourier.hpp"
