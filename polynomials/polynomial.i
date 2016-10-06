%module polynomial
%{
    #define SWIG_FILE_WITH_INIT
    #include "polynomial.hpp"
%}

%include "numpy.i"
%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* c, int p)};

%include "polynomial.hpp"
