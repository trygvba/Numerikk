%module polynomial
%{
    #define SWIG_FILE_WITH_INIT
    #include "polynomial.hpp"
%}

%include "numpy.i"
%include <std_string.i>

%init %{
    import_array();
%}

%apply (double* IN_ARRAY1, int DIM1) {(double* c, int p)};
%apply (double* ARGOUT_ARRAY1, int DIM1) { (double* output, int output_N) };


/****************************
 *      RENAMES:
 ****************************/
%rename("_get_all_coeffs")
        Polynomial1D::get_all_coeffs(double* output, int output_N) const;

/****************************
 *  INCLUDE DIRECTIVES:
 ****************************/
%include "polynomial.hpp"

/****************************
 *  EXTEND DIRECTIVES:
 ****************************/
%extend Polynomial1D {
    /* Incremental add: */
    void _iadd(const Polynomial1D& a){
        (*self) += a;
    }

    /* Incremental scaling: */
    void _imul(double a){
         (*self) *= a;
    }
    /* Incremental subtraction: */
    void _isub(const Polynomial1D& a){
        (*self) -= a;
    }

    /* For print(p) */
    std::string __str__(){
        std::ostringstream s;
        s << (*self);
        return s.str();
    }
    %pythoncode %{
        def get_all_coeffs(self):
            return self._get_all_coeffs(self.get_deg())

        def __iadd__(self, other):
            self._iadd(other)
            return self

        def __rmul__(self, a):
            self._imul(a)
            return self

        def __isub__(self, other):
            self._isub(other)
            return self
    %}
};
