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

    int getNsample() const {
        return nsample;
    }

  /*  void setNsample(int nsample) {
        FacadeForest::nsample = nsample;
    }*/

    int getMaxdepth() const {
        return maxheight;
    }


    bool isAdaptive() const {
        return adaptive;
    }

    bool isRangecheck() const {
        return rangecheck;
    }

    void setRangecheck(bool rangecheck) {
        FacadeForest::rangecheck = rangecheck;
    }


	const Forest* getIff() const {
		return iff;
	}

	/*const util::dataset* getTestdf() const {
		return testdf;
	}

	const util::dataset* getTraindf() const {
		return traindf;
	}

*/
    //Methods

    void trainForest(std::vector<std::vector<double> > &traindf,int _ntree,
    		int _nsample,int _maxheight, bool _rotate, bool _adaptive,
    		    		bool _rangecheck,double _rho,int _stopLimit);
    void trainForest(std::vector<std::vector<double> > &traindf,int _ntree,
        		int _nsample,int _maxheight, bool _rotate){
    	trainForest(traindf, _ntree, _nsample, _maxheight, _rotate,false,true,0.01,5);
    };


    void testForest(std::vector<std::vector<double> > &testdf);
    void saveModel(std::string modelName);
    //Forest loadModel(std::string modelName);
    std::vector<double> getScore();
    std::vector<std::vector<double> > pathLength();
    std::vector<double> averageDepth();
    long factorial(int n);
    /* Testing SWIG
;
    double sum_array(double* input_array, int length);
    void get_rand_array(double* output_array, int length);
    void sum_all( int nrow,int ncol,double* input_array);
    */
    void displayData();
};


#endif //IFOREST_ADDIN_FacadeForest_HPP







