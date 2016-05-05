//
// Created by zemichet on 3/30/16.
//

#ifndef FacadeFOREST_HPP
#define FacadeFOREST_HPP
#include "main.hpp"
//#include "utility.hpp"

class FacadeForest {
private:
    int ntree;
    int nsample;
    int maxheight;
    bool rotate;
    bool adaptive;
    bool rangecheck;
    double rho;
    int stoplimit;
    util::dataset *traindf;
    util::dataset *testdf;
    Forest *iff;
    float const ALPHA=0.01;
public:
    //constructor and Destructor
    virtual ~FacadeForest(){
    delete traindf;
    delete testdf;
    delete iff;
    };
    FacadeForest();

    int getNtree() const {
        return ntree;
    }

    void setNtree(int ntree) {
        FacadeForest::ntree = ntree;
    }

    int getNsample() const {
        return nsample;
    }

    void setNsample(int nsample) {
        FacadeForest::nsample = nsample;
    }

    int getMaxdepth() const {
        return maxheight;
    }

    void setMaxdepth(int maxdepth) {
        FacadeForest::maxheight = maxdepth;
    }

    bool isRotate() const {
        return rotate;
    }

    void setRotate(bool rotate) {
        FacadeForest::rotate = rotate;
    }

    bool isAdaptive() const {
        return adaptive;
    }

    void setAdaptive(bool adaptive) {
        FacadeForest::adaptive = adaptive;
    }

    bool isRangecheck() const {
        return rangecheck;
    }

    void setRangecheck(bool rangecheck) {
        FacadeForest::rangecheck = rangecheck;
    }

    //Methods

    void trainForest(std::vector<std::vector<double> > &traindf,int _ntree,
    		int _nsample,int _maxheight, bool _rotate, bool _adaptive,
    		    		bool _rangecheck,double _rho,int _stopLimit);
    void testForest(std::vector<std::vector<double> > &testdf);
    void saveModel(std::string modelName);
    //Forest loadModel(std::string modelName);
    std::vector<double> getScore();
    std::vector<std::vector<double> > PathLength();
    std::vector<double> averageDepth();

	const Forest* getIff() const {
		return iff;
	}

	const util::dataset* getTestdf() const {
		return testdf;
	}

	const util::dataset* getTraindf() const {
		return traindf;
	}
};


#endif //IFOREST_ADDIN_FacadeForest_HPP
