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
  // constructor 
  iForestRcpp(){};
  void train(NumericMatrix x_train, int n_trees, int num_sample, int max_height, bool rotate){
   
    auto vec =  to_vv(x_train);//Rcpp::as<std::vector<std::vector<double> > >(x_train);
  
    
    ff.train(vec, n_trees, num_sample, max_height, rotate);
  
    
  };
  std::vector<std::vector<double> > to_vv(NumericMatrix &df){
    int n_rows = df.nrow();
    int n_col = df.ncol();
    std::vector<std::vector<double> > vvd; 
    
    for(int i=0;i<n_rows;i++){
      std::vector<double> row = Rcpp::as<std::vector<double> >((NumericVector)df.row(i));
      vvd.push_back(row);
    }
    return vvd;
    
  }
  NumericMatrix path_length(){
    auto depths = ff.path_length();
    Rcpp::Rcout<<depths.size()<<depths[0].size();
    NumericMatrix nm_depths(depths[0].size(), depths.size());
    for(int i=0;i<depths[0].size();i++){
      for(int j=0;j<depths.size();j++)
 // #NumericVector nv(depths[i].begin(), depths[i].end());
      nm_depths(i,j) = depths[i][j];
    }
    return nm_depths;
  }
             //std::vector<int> const &column_index = std::vector<int>())
  NumericVector score(NumericMatrix x_test, bool check_missing_value = false){
    
    auto vec = to_vv(x_test);    //Rcpp::as<std::vector<std::vector<double> > >(x_test);
  
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
  
  // NumericVector path_length(NumericMatrix x_test){
  //   auto vec = to_vv(x_test);
  //   auto depths = ff.path_length(x_test)
  //   NumericVector nv_path()
  // }

};
// // [[Rcpp:export]]
// class TreeRcpp{
// private:
//   Tree itree;
// public:
//   void build_tree();
//   void depth();
//   
// };


RCPP_EXPOSED_CLASS_NODECL(iForestRcpp)
RCPP_MODULE(iForestModule) {
  class_<iForestRcpp>("iForestRcpp")
  .constructor()
  .method("train", &iForestRcpp::train)
  .method("score", &iForestRcpp::score)
  .method("path_length", &iForestRcpp::path_length)
  .method("save", &iForestRcpp::save)
  .method("load", &iForestRcpp::load);
}

