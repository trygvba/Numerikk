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
%apply (double* ARGOUT_ARRAY1, int DIM1) { (double* output, int output_N) };


// Rename section:
%rename("_get_evals") 
        FourierFunction::get_evals(double* output, int output_N);

// Include FILES:
%include "fourier.hpp"

// Need to extend with some Python code to get evals:
%extend FourierFunction {
    
    %pythoncode %{
        def get_evals(self):
            return self._get_evals(self.get_N())
    %}
};
