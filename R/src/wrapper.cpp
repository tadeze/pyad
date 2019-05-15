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
class iForest{
private:
  FacadeForest ff;
public:
  void train(NumericMatrix x_train, int n_trees, int num_sample, int max_height, bool rotate){
    ff.train(&x_train(0,0), n_trees, num_sample, max_height, rotate);
  
    
  };
             //std::vector<int> const &column_index = std::vector<int>())
  NumericVector score(NumericMatrix x_test, bool check_missing_value = false){
  auto  scores = ff.score(x_test(0,0), check_missing_value);
  NumericVector nv_score(scores.begin(), scores.end());
  return nv_score;
  }
  void load(const std::string &file_name, bool binaryFormat = true){
    ff.load(file_name, binaryFormat);
  }; //OUTPUT_FORMAT output_format);
  void save(const std::string &file_name, bool binaryFormat = true){
    ff.save(file_name, binaryFormat);
  }; //, OUTPUT_FORMAT output_format);
  
};


RCPP_MODULE(iForestModule) {
  class_<iForest>("iForest")
  .constructor()
  .method("train", &iForest::train)
  .method("score", &iForest::score)
  .method("save", &iForest::save)
  .method("load", &iForest::load);
}

