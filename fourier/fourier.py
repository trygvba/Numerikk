# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.5
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_fourier', [dirname(__file__)])
        except ImportError:
            import _fourier
            return _fourier
        if fp is not None:
            try:
                _mod = imp.load_module('_fourier', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _fourier = swig_import_helper()
    del swig_import_helper
else:
    import _fourier
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class FourierFunction(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FourierFunction, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FourierFunction, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _fourier.new_FourierFunction(*args)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _fourier.delete_FourierFunction
    __del__ = lambda self: None

    def get_N(self):
        return _fourier.FourierFunction_get_N(self)

    def get_Ncoeffs(self):
        return _fourier.FourierFunction_get_Ncoeffs(self)

    def get_eval(self, i):
        return _fourier.FourierFunction_get_eval(self, i)

    def _get_evals(self, output):
        return _fourier.FourierFunction__get_evals(self, output)

    def get_updated_status(self):
        return _fourier.FourierFunction_get_updated_status(self)

    def get_fourier_coefficient(self, i):
        return _fourier.FourierFunction_get_fourier_coefficient(self, i)

    def update_coefficients_from_evals(self):
        return _fourier.FourierFunction_update_coefficients_from_evals(self)

    def update_evals_from_coefficients(self):
        return _fourier.FourierFunction_update_evals_from_coefficients(self)

    def set_evals(self, in_eval):
        return _fourier.FourierFunction_set_evals(self, in_eval)

    def set_eval(self, i, val):
        return _fourier.FourierFunction_set_eval(self, i, val)

    def set_coefficient(self, i, cval):
        return _fourier.FourierFunction_set_coefficient(self, i, cval)

    def set_updated_status(self, status):
        return _fourier.FourierFunction_set_updated_status(self, status)

    def scale_coefficient(self, i, c_scale):
        return _fourier.FourierFunction_scale_coefficient(self, i, c_scale)

    def __add__(self, other):
        return _fourier.FourierFunction___add__(self, other)

    def __iadd__(self, other):
        return _fourier.FourierFunction___iadd__(self, other)

    def __imul__(self, a):
        return _fourier.FourierFunction___imul__(self, a)

    def __isub__(self, other):
        return _fourier.FourierFunction___isub__(self, other)

    def _add(self, a):
        return _fourier.FourierFunction__add(self, a)

    def _isub(self, a):
        return _fourier.FourierFunction__isub(self, a)

    def __str__(self):
        return _fourier.FourierFunction___str__(self)

    def _rmul(self, a):
        return _fourier.FourierFunction__rmul(self, a)

    def _mul(self, rval):
        return _fourier.FourierFunction__mul(self, rval)

    def _subtract(self, rval):
        return _fourier.FourierFunction__subtract(self, rval)

    def _imul(self, a):
        return _fourier.FourierFunction__imul(self, a)
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

FourierFunction_swigregister = _fourier.FourierFunction_swigregister
FourierFunction_swigregister(FourierFunction)


def diff(F):
    return _fourier.diff(F)
diff = _fourier.diff

def fejer_smoothing(f):
    return _fourier.fejer_smoothing(f)
fejer_smoothing = _fourier.fejer_smoothing
class FluxFunctionBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, FluxFunctionBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, FluxFunctionBase, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _fourier.delete_FluxFunctionBase
    __del__ = lambda self: None

    def evaluate(self, u):
        return _fourier.FluxFunctionBase_evaluate(self, u)
FluxFunctionBase_swigregister = _fourier.FluxFunctionBase_swigregister
FluxFunctionBase_swigregister(FluxFunctionBase)

class FluxFunctionPower(FluxFunctionBase):
    __swig_setmethods__ = {}
    for _s in [FluxFunctionBase]:
        __swig_setmethods__.update(getattr(_s, '__swig_setmethods__', {}))
    __setattr__ = lambda self, name, value: _swig_setattr(self, FluxFunctionPower, name, value)
    __swig_getmethods__ = {}
    for _s in [FluxFunctionBase]:
        __swig_getmethods__.update(getattr(_s, '__swig_getmethods__', {}))
    __getattr__ = lambda self, name: _swig_getattr(self, FluxFunctionPower, name)
    __repr__ = _swig_repr

    def __init__(self, *args):
        this = _fourier.new_FluxFunctionPower(*args)
        try:
            self.this.append(this)
        except:
            self.this = this
    __swig_destroy__ = _fourier.delete_FluxFunctionPower
    __del__ = lambda self: None

    def evaluate(self, u):
        return _fourier.FluxFunctionPower_evaluate(self, u)

    def get_n(self):
        return _fourier.FluxFunctionPower_get_n(self)

    def __str__(self):
        return _fourier.FluxFunctionPower___str__(self)
FluxFunctionPower_swigregister = _fourier.FluxFunctionPower_swigregister
FluxFunctionPower_swigregister(FluxFunctionPower)

# This file is compatible with both classic and new-style classes.


