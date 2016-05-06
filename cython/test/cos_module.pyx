#cdef extern from "math.h":
#    double cos(double arg)

from libc.math cimport cos
def cos_func(arg):
    return cos(arg)
