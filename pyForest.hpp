//
// Created by zemichet on 3/30/16.
//

#ifndef IFOREST_ADDIN_PYFOREST_HPP
#define IFOREST_ADDIN_PYFOREST_HPP
#include<string>
#include <boost/python.hpp>
#include <cstdint>
#include <string>
#include <vector>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>



class pyForest {
private:
    int ntree;
    int nsample;
    int maxdepth;
    bool rotate;
    bool adaptive;
    bool rangecheck;
public:
    int getNtree() const {
        return ntree;
    }

    void setNtree(int ntree) {
        pyForest::ntree = ntree;
    }

    int getNsample() const {
        return nsample;
    }

    void setNsample(int nsample) {
        pyForest::nsample = nsample;
    }

    int getMaxdepth() const {
        return maxdepth;
    }

    void setMaxdepth(int maxdepth) {
        pyForest::maxdepth = maxdepth;
    }

    bool isRotate() const {
        return rotate;
    }

    void setRotate(bool rotate) {
        pyForest::rotate = rotate;
    }

    bool isAdaptive() const {
        return adaptive;
    }

    void setAdaptive(bool adaptive) {
        pyForest::adaptive = adaptive;
    }

    bool isRangecheck() const {
        return rangecheck;
    }

    void setRangecheck(bool rangecheck) {
        pyForest::rangecheck = rangecheck;
    }

    void trainForest();
    void saveModel(std::string modelName);
    Forest loadModel(std::string modelName);
    double getScore(std::string testdata);
    virtual ~pyForest(){};
    pyForest();
};


#endif //IFOREST_ADDIN_PYFOREST_HPP
