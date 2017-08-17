//
// Created by tadeze on 4/5/17.
//

#include "math.hpp"
//#include "Tree.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
//#include "metric.hpp"
namespace py = pybind11;
/*
class Math{
public:
    double square(double x){
        return x*x;
    }
    Math(){};
    virtual ~Math(){};

};*/
double inverse(double n){
      return 1/n;
}
PYBIND11_PLUGIN(pyTree){
    pybind11::module m("pyTree", "auto-compiled c++ extension");
    m.def("inverse",py::vectorize(inverse));
  //m.def("add",metric::add);
  pybind11::class_<Math>(m,"Math")
           .def(py::init())
           .def("square",& Math::square);
//    pybind11::class_<Tree>(m,"Tree")
//            .def(py::init())
//                    .def("")
    return m.ptr();

    // pybind11::module m("pyTree", "auto-compiled c++ extension");
    //m.def("square",py::vectorize());
    return m.ptr();
}
