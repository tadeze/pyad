
%module pyFacade
%{ 
    #define SWIG_FILE_WITH_INIT
    #include "../FacadeForest.hpp"
%}

/* Include the NumPy typemaps library */
%include "numpy.i"

%init %{
  import_array();
%}

/* Typemap for the sum_list(double* input_list, int length) C/C++ routine */
%apply (double* IN_ARRAY1, int DIM1) {(double* input_array, int length)};
/* Typemap for the get_rand_array(double* output_array, int length) C/C++ routine */
%apply (double* ARGOUT_ARRAY1, int DIM1) {(double* output_array, int length)};

%include "../FacadeForest.hpp"








