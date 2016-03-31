//
// Created by zemichet on 3/30/16.
//

#include "pyForest.hpp"




void pyForest::trainForest() {

}

void pyForest::saveModel(std::string modelName) {

}

std::object pyForest::loadModel(std::string modelName) {
    return nullptr;
}

double pyForest::getScore(std::string testdata) {
    return 0;
}

pyForest::pyForest() {

}



/*
 * This is a macro Boost.Python provides to signify a Python extension module.
 */
BOOST_PYTHON_MODULE(pyForest) {
    // An established convention for using boost.python.
    using namespace boost::python;

    // Expose the function hello().
    //def("hello", hello);

    // Expose the class pyForest.
    class_<Animal>("pyForest",
                   init<std::string const &>())
            .def("saveModel", &pyForest::saveModel)
            .def("loadModel", &pyForest::loadModel)
            .def("getScore", &pyForest::getScore)
            .add_property("ntree", &pyForest::getNtree, &pyForest::setNtree);

}
