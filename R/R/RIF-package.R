#' @name RIF
#' @author T
#' @docType package
#' @useDynLib RIF
#' @importFrom Rcpp evalCpp
#' @importFrom Rcpp cpp_object_initializer
#' @importClassesFrom Rcpp "C++Object"
#' @importFrom methods new
NULL

.onUnload <- function(libpath) {
  library.dynam.unload("RIF", libpath)
}

Rcpp::loadModule("iForestModule", TRUE)
