#include <Rcpp.h>
#include "facade_forest.hpp"
using namespace Rcpp;
using namespace osu::ad;
// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//
//int num_tree,
//[[Rcpp::plugins("cpp11")]]
// [[Rcpp:export]]
class iForestRcpp{
private:
  FacadeForest ff;
public:
  void train(NumericMatrix x_train, int n_trees, int num_sample, int max_height, bool rotate){
    Rcout<<x_train.size();
    auto vec = Rcpp::as<std::vector<std::vector<double> > >(x_train);
  
    
    ff.train(vec, n_trees, num_sample, max_height, rotate);
  
    
  };
  
             //std::vector<int> const &column_index = std::vector<int>())
  NumericVector score(NumericMatrix x_test, bool check_missing_value = false){
    
    auto vec = Rcpp::as<std::vector<std::vector<double> > >(x_test);
  
    auto  scores = ff.score(vec, check_missing_value);
    NumericVector nv_score(scores.begin(), scores.end());
    return nv_score;
  }
  
  void load(const std::string &file_name, bool binaryFormat = true){
    ff.load(file_name, binaryFormat);
  }; //OUTPUT_FORMAT output_format);
  
  void save(const std::string &file_name, bool binaryFormat = true){
    ff.save(file_name, binaryFormat);
  }; //, OUTPUT_FORMAT output_format);
  
  // constructor 
  iForestRcpp(){};
};

RCPP_EXPOSED_CLASS_NODECL(iForestRcpp)
RCPP_MODULE(iForestModule) {
  class_<iForestRcpp>("iForestRcpp")
  .constructor()
  .method("train", &iForestRcpp::train)
  .method("score", &iForestRcpp::score)
  .method("save", &iForestRcpp::save)
  .method("load", &iForestRcpp::load);
}

