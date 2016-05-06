//
// Created by zemichet on 3/30/16.
//

#include "FacadeForest.hpp"
#include<exception>

void FacadeForest::saveModel(std::string modelName) {
	std::cout << modelName << " Place holder";
}

FacadeForest::FacadeForest() {
	ntree = 0;
	nsample = 0;
	rotate = false;
	maxheight = 0;
	adaptive = false;
	rangecheck = false;
	traindf = nullptr;
	testdf = nullptr;
	rho = 0.01;
	stoplimit = 0;
	iff = nullptr;

}
util::dataset *makeDataset(std::vector<std::vector<double> > &data) {
	util::dataset *dt = new util::dataset();
	dt->data = data;
	dt->ncol = (int) data[0].size();
	dt->nrow = (int) data.size();
	return dt;
}

void FacadeForest::trainForest(std::vector<std::vector<double> > &traindf,
		int _ntree, int _nsample, int _maxheight, bool _rotate, bool _adaptive,
		bool _rangecheck, double _rho, int _stopLimit) {

	ntree = _ntree;
	nsample = _nsample;
	rotate = _rotate;
	maxheight = _maxheight;
	adaptive = _adaptive;
	rangecheck = _rangecheck;
	rho = _rho;
	stoplimit = _stopLimit;

	bool rsample = nsample != 0;
	bool stopheight = maxheight != 0;
	this->traindf = makeDataset(traindf);

	if (!rotate) {
		IsolationForest *iforest = new IsolationForest(ntree, this->traindf,
					nsample, maxheight, stopheight, rsample); //build iForest
			iff = iforest;
		}
	else{
		IsolationForest *iforest = new IsolationForest(ntree, this->traindf,
							nsample, maxheight, stopheight, rsample); //build iForest
		//std::cout<<"Output from rforest\n";
		iff = iforest;

	}

	try {
				if (adaptive)
					iff->adaptiveForest(rho, stoplimit);
				else
					iff->fixedTreeForest();  //just for now build fixed tree
			} catch (std::exception& e) {
				std::cout << "Standard exception: " << e.what() << std::endl;
			}

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
	// std::vector<double> scores = {2,3,0.4,0.9,78};
	return iff->AnomalyScore(testdf);
	//return this->testdf->data[0];

}

std::vector<std::vector<double> > FacadeForest::pathLength() {

	return iff->pathLength(testdf);

}

std::vector<double> FacadeForest::averageDepth() {
	std::vector<double> meandepth;
	for (std::vector<double> row : this->pathLength()) {
		meandepth.push_back(util::mean(row));
	}
	return meandepth;
}

long FacadeForest::factorial(int n) {
	long fact = 1;
	for (int i = 1; i <= n; i++)
		fact *= i;
	return fact;
}



void FacadeForest::displayData() {
	std::cout << " Dimension of training data (" << this->traindf->nrow << ","
			<< this->traindf->ncol << ")\n";
	for (auto row : this->traindf->data) {
		for (auto cell : row)
			std::cout << cell << "\t";
		std::cout << "\n";
	}

}

