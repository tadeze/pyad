#include <cmath>
#include "cos_doubles.hpp"
#include "squareit.hpp"
/*  Compute the cosine of each element in in_array, storing the result in
 *  out_array. */
void cos_doubles(double * in_array, double * out_array, int size){
    int i;
    for(i=0;i<size;i++){
        out_array[i] = cos(square(in_array[i]));
    }
}
