//
// Created by zemichet on 3/30/16.
//

#include "FacadeForest.hpp"
#include<exception>
#include<fstream>
FacadeForest::FacadeForest() {
	ntree = 0;
	nsample = 0;
	rotate = false;
	maxHeight = 0;
	adaptive = false;
	rangeCheck = false;
	traindf = nullptr;
	testdf = nullptr;
	rho = 0.01;
	stopLimit = 0;
	iff = nullptr;

}
util::dataset *makeDataset(std::vector<std::vector<double> > &data) {
	util::dataset *dt = new util::dataset();
	dt->data = data;
	dt->ncol = (int) data[0].size();
	dt->nrow = (int) data.size();
	return dt;
}

//Check if the forest is built correctly
int FacadeForest::isValidModel() const{

    if(iff==nullptr)
       //std::cout<<"Forest model not yet trained\n";
     return FOREST_NOT_TRAINED;

     //Check if test data is available
    if(testdf==nullptr || testdf->nrow==0)
        	return NO_TEST_DATA;

   	return OK;
   	/*catch (std::exception& e) {
			std::cout << "Standard exception: " << e.what() << std::endl;
*/
    //return true;
}
void FacadeForest::trainForest(std::vector<std::vector<double> > &traindf,
		int _ntree, int _nsample, int _maxheight, bool _rotate, bool _adaptive,
		bool _rangecheck, double _rho, int _stopLimit) {

	ntree = _ntree;
	nsample = _nsample;
	rotate = _rotate;
	maxHeight = _maxheight;
	adaptive = _adaptive;
	rangeCheck = _rangecheck;
	rho = _rho;
	stopLimit = _stopLimit;

	bool rsample = nsample != 0;
	bool stopheight = maxHeight != 0;
	this->traindf = makeDataset(traindf);

	if (!rotate) {
		IsolationForest *iforest = new IsolationForest(ntree, this->traindf,
					nsample, maxHeight, stopheight, rsample); //build iForest
			iff = iforest;
		}
	else{
		IsolationForest *iforest = new IsolationForest(ntree, this->traindf,
							nsample, maxHeight, stopheight, rsample); //build iForest
		//std::cout<<"Output from rforest\n";
		iff = iforest;

	}

	try {
				if (adaptive)
					iff->adaptiveForest(rho, stopLimit);
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

    //Make sure the forest is built and test data is available
     //isValidModel()

	return iff->AnomalyScore(testdf);

}

std::vector<std::vector<double> > FacadeForest::pathLength() {
   /*  if(!isValidModel())
         std::exit(1);
   */
	return iff->pathLength(testdf);

}

std::vector<double> FacadeForest::averageDepth() {
    /*if(!isValidModel())
      std::exit(1);
    */
      std::vector<double> meandepth;
	for (std::vector<double> row : this->pathLength()) {
		meandepth.push_back(util::mean(row));
	}
	return meandepth;
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
 void FacadeForest::saveModel(std::string modelName) {
  // Save the json representation 
  
 std::string jsonstr = iff->to_json().dump();
 std::ofstream  out(modelName);

 out<<jsonstr;
 //std::cout<<jsonstr<<" Json representation "<<modelName;

 }
