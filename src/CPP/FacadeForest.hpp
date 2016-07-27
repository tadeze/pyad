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
    int maxHeight;
    bool rotate;
    bool adaptive;
    bool rangeCheck;
    double rho;
    int stopLimit;
    util::dataset *traindf;
    util::dataset *testdf;
    Forest *iff;

    const int FOREST_NOT_TRAINED=1;
    const int NO_TEST_DATA =2;
    const int OK =0;


  public:
    //constructor and Destructor
    virtual ~FacadeForest(){
    delete traindf;
    delete testdf;
    delete iff;
    };
    FacadeForest();

    
    int getNTree() const {
        return ntree;
    }

    int getNSample() const {
        return nsample;
    }

  /*  void setNsample(int nsample) {
        FacadeForest::nsample = nsample;
    }*/

    int getMaxDepth() const {
        return maxHeight;
    }


    bool isAdaptive() const {
        return adaptive;
    }
    bool isRotate() const {
        return rotate;
    }
    bool isRangeCheck() const {
        return rangeCheck;
    }

    void setRangeCheck(bool rangecheck) {
        FacadeForest::rangeCheck = rangecheck;
    }


	const Forest* getIff() const {
		return iff;
	}

	const util::dataset* getTestdf() const {
		return testdf;
	}

	const util::dataset* getTraindf() const {
		return traindf;
	}


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
    void loadModel(std::string modelName);
    std::vector<double> getScore();
    std::vector<std::vector<double> > pathLength();
    std::vector<double> averageDepth();


    /* Testing SWIG
;
    double sum_array(double* input_array, int length);
    void get_rand_array(double* output_array, int length);
    void sum_all( int nrow,int ncol,double* input_array);
    */
    void displayData();
    int isValidModel() const;
};


#endif //IFOREST_ADDIN_FacadeForest_HPP
