%module fourier
%{
    #define SWIG_FILE_WITH_INIT
    #include "fourier.hpp"
%}

%include "numpy.i"
%include <std_string.i>
%init %{
    import_array();
%}

/**************************
 *      TYPEMAPS:
 **************************/
%apply (double* IN_ARRAY1, int DIM1) {(double* in_eval, int in_N)};
%apply (double ARGOUT_ARRAY1[ANY]) { (double out[2]) };
%apply (double* ARGOUT_ARRAY1, int DIM1) { (double* output, int output_N) };


/**************************
 *      RENAMES:
 **************************/
%rename("_get_evals") 
        FourierFunction::get_evals(double* output, int output_N) const;

/**************************
 *  INCLUDE FILES:
 **************************/
%include "fourier.hpp"

/**************************
 *  EXTEND DIRECTIVE:
 **************************/
%extend FourierFunction {
    /* Need for incremental add, memory management: */
    void _add(const FourierFunction& a){
        (*self) += a;
    }

    /* Needed for incremantal sub, memory management: */
    void _isub(const FourierFunction& a){
        (*self) -= a;
    }
    /* For print(F) statement */
    std::string __str__(){
        std::ostringstream s;
        s << (*self);
        return s.str();
    }
    /* For scaling by a double */
    FourierFunction _rmul(double a){
        return a*(*self);
    }
    
    /* For multiplication by two functions: */
    FourierFunction _mul(FourierFunction& rval){
        return (*self)*rval;
    }
    /* For subtraction */
    FourierFunction _subtract(const FourierFunction& rval){
        return (*self) - rval;
    }

    /* For incremental scaling */
    void _imul(double a){
        (*self) *= a;
    }

    /*************************************
     * Python code for some magic methods
     *************************************/
    %pythoncode %{
        def get_evals(self):
            return self._get_evals(self.get_N())
        
        def __iadd__(self, other):
            self._add(other)
            return self
        
        def __rmul__(self, a):
            return self._rmul(a)

        def __mul__(self, other):
            return self._mul(other)

        def __imul__(self, a):
            self._imul(a);
            return self

        def __sub__(self, rval):
            return self._subtract(rval)

        def __isub__(self, rval):
            self._isub(rval)
            return self
    %}
};
