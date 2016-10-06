%module fourier
%{
    #define SWIG_FILE_WITH_INIT
    #include "fourier.hpp"
%}

%include "numpy.i"
%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* in_evals, int in_N)};

%include "fourier.hpp"
