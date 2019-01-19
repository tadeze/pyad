
# c++ interface to cython
from libcpp.vector cimport vector
from libcpp.map cimport map
from libcpp cimport bool
from libcpp.string cimport string

cdef extern from "src/facade_forest.hpp" namespace "osu::ad":
    cdef cppclass FacadeForest "osu::ad::FacadeForest":
        FacadeForest()
        void displayData(vector[vector[double]]&)
        int trainForest(vector[vector[double]] &, int, int, int,
                        bool, bool, bool, double, int,vector[int]&)
        void testForest(vector[vector[double]] &, bool)
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
        void save(string model_name)
        void load(string model_name)
        map[int, double] explanation(vector[double] &)

cdef extern from "src/tree.hpp" namespace "osu::ad":
    cdef cppclass Tree "osu::ad::Tree":
        Tree()
        void iTree(vector[int] &, vector[vector[double]], int, int, bool, vector[int] &)
        double pathLength(vector[double] &, bool)
        int maxTreeDepth()
        int getNodeSize()
        int getSplittingAtt()
        double getSplittingPoint()
        int getDepth()
        double getMinAttVal()
        double getMaxAttVal()
        map[int, double] explanation(vector[double] &)
