/*<%

cfg['compiler_args'] = ['-std=c++11']
cfg['sources'] = ['../utility.cpp','../Tree.cpp','../FacadeForest.cpp','../Forest.cpp',
    '../IsolationForest.cpp','wrapper.cpp']
setup_pybind11(cfg)
%>
*/
#include "../FacadeForest.hpp"
#include "pybind11/pybind11.h"
#include "pybind11/numpy.h"
/*
//Request return a structure of the following
struct buffer_info {
    void *ptr;
    size_t itemsize;
    std::string format;
    int ndim;
    std::vector<size_t> shape;
    std::vector<size_t> strides;
};
*/
namespace py = pybind11;

double square(double x)
{
  return x*x;
}

void twice(py::array_t<double> xs) {
    py::buffer_info info = xs.request();
    auto ptr = static_cast<double *>(info.ptr);

    int n = 1;
    for (auto r: info.shape) {
      n *= r;
    }

    for (int i = 0; i <n; i++) {
        *ptr++ *= 2;
    }
}
// Passing in a generic array
double sum(py::array xs) {
    py::buffer_info info = xs.request();
    auto ptr = static_cast<double *>(info.ptr);

    int n = 1;
    for (auto r: info.shape) {
      n *= r;
    }

    double s = 0.0;
    for (int i = 0; i <n; i++) {
        s += *ptr++;
    }

    return s;
}

PYBIND11_PLUGIN(pyiforest) {
  /*
  void displayData()
        void trainForest(vector[vector[double]] &, int ,int,int,bool,bool,bool,double,int)
        void testForest(vector[vector[double]] &)
        long factorial(int)
        vector[double]  getScore()
        vector[vector[double]] pathLength()
        vector[double] averageDepth()
        int getNTree()
        int getNSample()
        int getMaxDepth()
        bool isAdaptive()
        bool isRangeCheck()
        bool isRotate()
        int isValidModel()
        void saveModel(string model_name)
        void loadModel(string model_name,string forest_type)

  */
    py::module m("pyiforest", "iforest bind using pybind11");
    m.def("square",py::vectorize(square));  //vectorize a function.
    m.def("sum", &sum);
    m.def("twice", &twice);
    py::class_<FacadeForest>(m,"FacadeForest")
    .def(py::init<>())
    .def("displayData",&FacadeForest::displayData)
    .def("trainForest",(void (FacadeForest::*)(std::vector<std::vector<double> > &, int,
    		int, int, bool, bool, bool, double, int)) &FacadeForest::trainForest) //overloaded method for trainForest
    //.def("trainForest",&FacadeForest::trainForest)
    .def("testForest",&FacadeForest::testForest)
    .def("getScore",&FacadeForest::getScore)
    .def("averageDepth",&FacadeForest::averageDepth)
    .def("pathLength",&FacadeForest::pathLength)
    .def("saveModel",&FacadeForest::saveModel)
    .def("loadModel",&FacadeForest::loadModel);
  /*        m.def("mult",&mult, " A funct which multiplies",
          "i"_a=1, "j"_a=2
        );
          m.def("fact",&fact," AF unction which compute factorial",
        "i"_a=1);
*/
    return m.ptr();
}
