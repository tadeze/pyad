//
// Created by zemichet on 3/30/16.
//

#include "facade_forest.hpp"
#ifdef  SERIALIZATION
#include <cereal/archives/json.hpp>
#include "cereal/archives/binary.hpp"
#endif

#include<cmath>
using namespace osu::ad;
//std::ofstream util::log_file("logfile2.csv");

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

std::shared_ptr<util::Dataset> make_dataset(util::DoubleMatrix &data) {
  /*
   * @param data: DoubleMatrix input data
   *
   */

  std::shared_ptr<util::Dataset> dt = std::make_shared<util::Dataset>();
  //auto dt = std::make_shared<util::Dataset>();
  dt->data = data;
  dt->ncol = (int) data[0].size();
  dt->nrow = (int) data.size();
  return dt;
}

//Check if the forest is built correctly
int FacadeForest::isValidModel() const {

  if (iff == nullptr)
    //std::cout<<"Forest model not yet trained\n";
    return FOREST_NOT_TRAINED;

  //Check if test data is available
  if (testdf == nullptr || testdf->nrow == 0)
    return NO_TEST_DATA;

  return OK;
  /*catch (std::exception& e) {
       std::cout << "Standard exception: " << e.what() << std::endl;
*/
  //return true;
}

int FacadeForest::trainForest(util::DoubleMatrix &traindf,
                              int _ntree, int _nsample, int _maxheight, bool _rotate, bool _adaptive,
                              bool _rangecheck, double _rho, int _stopLimit, std::vector<int> const &columnIndex) {

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
  this->traindf = make_dataset(traindf);

  if (!rotate) {
    //	IsolationForest *iforest
    iff = std::make_shared<IsolationForest>(ntree, this->traindf,
                                            nsample, maxHeight, stopheight, rsample, columnIndex); //build iForest
    //		iff = iforest;
  } else { // For now just use IsolationForest until changed.
    iff = std::make_shared<IsolationForest>(ntree, this->traindf,
                                            nsample, maxHeight, stopheight, rsample, columnIndex); //build iForest
  }

  try {
    if (adaptive)
      ntree = iff->adaptive_forest(rho, stopLimit);

    else
      iff->fixed_forest();  //just for now build fixed tree
  } catch (std::exception &e) {
    std::cout << "Standard exception: " << e.what() << std::endl;
  }
  return ntree;  //Return number of trees_ used. Useful incase of adaptive tree growing
}

void FacadeForest::testForest(std::vector<std::vector<double> > &_testdf, bool cmv) {

  this->testdf = make_dataset(_testdf);
  iff->check_missing_value_ = cmv;
}

/*
 Forest FacadeForest::loadModel(std::string modelName) {

 return nullptr;
 }
 */

std::vector<double> FacadeForest::getScore() {

  //Make sure the forest is built and test data is available
  //isValidModel()

  return iff->anomaly_score(testdf);

}

std::vector<std::vector<double> > FacadeForest::pathLength() {
  /*  if(!isValidModel())
        std::exit(1);
  */
  return iff->path_length(testdf);

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

void FacadeForest::displayData(std::vector<std::vector<double> > &_df) {
  auto df = make_dataset(_df);
  std::cout << " Dimension of training data (" << df->nrow << ","
            << df->ncol << ")\n";
  for (auto row : df->data) {
    for (auto cell : row) {
      double ff = std::isnan(cell) ? -9999.0 : cell;
      std::cout << ff << "\t";
    }
    std::cout << "\n";
  }

}
#ifdef SERIALIZATION
void FacadeForest::load(const std::string &filename, bool binaryFormat) {
  std::ifstream file{filename};
  if (!file.is_open()) {
    throw std::runtime_error{filename + " could not be opened"};
  }
  if (binaryFormat) {
    cereal::BinaryInputArchive archive{file};
    // TODO:support for JSON format
    archive(cereal::make_nvp("num_trees_", ntree), cereal::make_nvp("num_sample_", nsample),
            cereal::make_nvp("maxHeight", maxHeight), cereal::make_nvp("stopLimit", stopLimit),
            cereal::make_nvp("rho", rho), cereal::make_nvp("rotate", rotate),
            cereal::make_nvp("adaptive", adaptive), cereal::make_nvp("forest", iff));
  } else {
    cereal::JSONInputArchive archive{file};
    // TODO:support for JSON format
    archive(cereal::make_nvp("num_trees_", ntree), cereal::make_nvp("num_sample_", nsample),
            cereal::make_nvp("maxHeight", maxHeight), cereal::make_nvp("stopLimit", stopLimit),
            cereal::make_nvp("rho", rho), cereal::make_nvp("rotate", rotate),
            cereal::make_nvp("adaptive", adaptive), cereal::make_nvp("forest", iff));

  }
}

void FacadeForest::save(const std::string &filename, bool binaryFormat) {
  std::ofstream file{filename};
  if (!file.is_open()) {
    throw std::runtime_error{filename + " could not be opened"};
  }
  if (binaryFormat) {
    cereal::BinaryOutputArchive archive{file};

    archive(cereal::make_nvp("num_trees_", ntree), cereal::make_nvp("num_sample_", nsample),
            cereal::make_nvp("maxHeight", maxHeight), cereal::make_nvp("stopLimit", stopLimit),
            cereal::make_nvp("rho", rho), cereal::make_nvp("rotate", rotate),
            cereal::make_nvp("adaptive", adaptive), cereal::make_nvp("forest", iff));
  } else {
    cereal::JSONOutputArchive archive{file};
    archive(cereal::make_nvp("num_trees_", ntree), cereal::make_nvp("num_sample_", nsample),
            cereal::make_nvp("maxHeight", maxHeight), cereal::make_nvp("stopLimit", stopLimit),
            cereal::make_nvp("rho", rho), cereal::make_nvp("rotate", rotate),
            cereal::make_nvp("adaptive", adaptive), cereal::make_nvp("forest", iff));
  }

}
#else
void FacadeForest::save(const std::string &filename, bool binaryFormat){
    std::cerr<<"Save method is not defined in windows OS";
}
void FacadeForest::load(const std::string &filename, bool binaryFormat){
    std::cerr<<"Load method is not defined windows OS";
}
#endif

std::map<int, double> FacadeForest::explanation(std::vector<double> &inst) {
  return iff->importance(inst);
}


