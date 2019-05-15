#' Train R IsolationForest algorithm
#' @param train a matrix of training dataset
#' @param ntrees the number of trees
#' @param nsample number of subsample size
#' @param height depth of tree to grow. If 0, grow to full depth
#' @param rotate rotate data before growing  trees. Default False 
#'@export


isolation_trees.RIF<-function(x, ntrees=100, nsample=512, height=0, rotate=FALSE){
  
  x_train <- as.matrix(x)
  if(nsample>nrow(x_train)){
    nsample <- nrow(x_train)
  }
  feature_size = ncol(x_train)
  forest <- methods::new(iForestRcpp)
  forest$train(x_train, ntrees, nsample, height, rotate)
  return(structure(list(
    iforest=forest), class="RIF"))
}
#' Score anomaly score from  trained forest.
#' @param x a matrix of test dataset with equal
#' @param rif trained IsolationForest type object
#' @param check_missing if TRUE handles missing value for test data. 
anomaly_score.RIF<-function(rif, x, check_missing=TRUE){
  x_test <- as.matrix(x)
  # if(ncol(x_test)!=rif$feature_size){
  #   stop("The number of features in test data should be equal to the training dataset.")
  # }
  score <- rif$iforest$score(x_test, check_missing)
  return(score)
}
#' Print method for RIF objects 
print.RIF <-function(x,...){
  cat(format(x$iforest,...),sep="\n")
}
#' Output path length or depth of the points
path_length.RIF <-function(rif, x){
  x_test <- as.matrix(x)
  # if(ncol(x_test)!=rif$feature_size){
  #   stop("The number of features in test data should be equal to the training dataset.")
  # }
  return(rif$iforest$path_length(x_test))
}

#' Save module to file 
#' @param rif RIF trained object 
#' @param file_name full name for the file path to save. 
#' @param binary_format if true save as binary otherwise save as JSON format

save.RIF <-function(rif, file_name, binary_format=TRUE){
  rif$iforest$save(file_name, binary_format)
}

#' Load RIF object from file 
#' @param file_name full path for the saved object 
#' @param binary_format type of the file to deserialize. 
#' @return RIF object
#'  @export 
load.RIF <-function(file_name, binary_format=TRUE){
  iforest <- methods::new(iForestRcpp)
  iforest$load(file_name, binary_format)
  return (structure(list(iforest=iforest),class="RIF"))
}

