//
// Created by zemichet on 3/30/16.
//

#include "FacadeForest.hpp"


void FacadeForest::saveModel(std::string modelName) {
std::cout<<modelName<<" Place holder";
}


FacadeForest::FacadeForest()
{
	ntree = 0;
	nsample =0; 
	rotate =false;
	maxheight=0;
	adaptive = false;
	rangecheck =false;
	traindf = nullptr;
	testdf = nullptr;
	rho =0.01;
	stoplimit =0;
	iff = nullptr;


}


void FacadeForest::trainForest(std::vector<std::vector<double> > &traindf,int _ntree,int _nsample,int _maxheight,
		bool _rotate, bool _adaptive,bool _rangecheck,double _rho,int _stopLimit){

	ntree = _ntree;
	nsample = _nsample;
	rotate = _rotate;
	maxheight= _maxheight;
	adaptive = _adaptive;
	rangecheck = _rangecheck;
	rho = _rho;
	stoplimit = _stopLimit;


	bool rsample = nsample != 0;
	bool stopheight = maxheight != 0;
	this->traindf = makeDataset(traindf);

	if(!rotate)
	{
		IsolationForest *iforest = new IsolationForest(ntree,this->traindf,nsample,maxheight,stopheight,rsample); //build iForest
		iff = iforest;


	}

//	else{
//		//RForest rff(ntree,this->traindf,nsample,maxheight,stopheight,rsample);
//		//string rot_output(output_name);
//		//buildForest(rff,test_dt,alpha,stopLimit,rho,"rotate_"+rot_output,metadata,pathlength);
//	//	iff = &rff;
//		///For now skip it
//	continue;
//	}

	iff->fixedTreeForest();  //just for now build fixed tree


}



void FacadeForest::testForest(std::vector<std::vector<double> > &_testdf) {

    	//morph _testdf vector to doublerame format.

	this->testdf = makeDataset(_testdf);

	}


/*
Forest FacadeForest::loadModel(std::string modelName) {

	return nullptr;
}
*/

std::vector<double> FacadeForest::getScore() {

//	if(testdf==nullptr)
//		return std::exit(0); //For now just exit

    return iff->AnomalyScore(testdf);

}


std::vector<std::vector<double> > FacadeForest::PathLength() {

	return iff->pathLength(testdf);

}

std::vector<double> FacadeForest::averageDepth() {
	std::vector<double> meandepth(testdf->nrow);
	for(std::vector<double> row : this->PathLength())
	{
		meandepth.push_back(util::mean(row));
	}
return meandepth;
}






