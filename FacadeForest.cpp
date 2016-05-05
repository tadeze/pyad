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
util::dataset *makeDataset(std::vector<std::vector<double> > &data)
{
	util::dataset *dt = new util::dataset();
	dt->data = data;
	dt->ncol = (int)data[0].size();
	dt->nrow = (int)data.size();
	return dt;
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

//	else{ skip for now
//		//RForest rff(ntree,this->traindf,nsample,maxheight,stopheight,rsample);
//		//string rot_output(output_name);
//		//buildForest(rff,test_dt,alpha,stopLimit,rho,"rotate_"+rot_output,metadata,pathlength);
//	//	iff = &rff;
//		///For now skip it
//	continue;
//	}
//
	if(adaptive)
		iff->adaptiveForest(ALPHA,stoplimit);
	else
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
	std::vector<double> meandepth;
	for(std::vector<double> row : this->PathLength())
	{
		meandepth.push_back(util::mean(row));
	}
return meandepth;
}

long FacadeForest::factorial(int n){
	long fact =1;
	for(int i=1;i<=n;i++)
		fact *=i;
	return fact;
}


double FacadeForest::sum_array(double* input_array, int length) {

  /* Initialize sum */
  double sum = 0.;

  /* Compute sum of array elements */
  for (int i=0; i < length; i++)
    sum += input_array[i];

  return sum;
}
/* Define function implementation */
void FacadeForest::get_rand_array(double* output_array, int length) {

  /* Populate input NumPy array with random numbers */
  for (int i=0; i < length; i++)
    output_array[i] = ((double) rand()) / RAND_MAX;

  return;
}




