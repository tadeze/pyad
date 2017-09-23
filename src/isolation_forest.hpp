/*
 * IsolationForest.hpp
 *
 *  Created on: May 5, 2015
 *      Author: tadeze
 */

#ifndef ISOLATIONFOREST_HPP_
#define ISOLATIONFOREST_HPP_
#include "forest.hpp"
#include "cereal/types/polymorphic.hpp"
class IsolationForest:public Forest{
    public:
	IsolationForest(){};

	IsolationForest(int _ntree, std::shared_ptr<util::dataset> _df,
			int _nsample,int _maxheight, bool _stopheight,bool _rsample);
	//int adaptiveForest(double alpha,int stopLimit);
	void buildForest();
	virtual ~IsolationForest()
	{
	}
	//convergent iForest
  int adaptiveForest(double alpha,int stopLimit); 
  void fixedTreeForest();
  int confTree(double alpha,double rho,int init_tree);

};

CEREAL_REGISTER_TYPE(IsolationForest);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Forest,IsolationForest);
#endif /* ISOLATIONFOREST_HPP_ */
