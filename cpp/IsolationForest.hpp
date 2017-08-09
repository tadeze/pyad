/*
 * IsolationForest.hpp
 *
 *  Created on: May 5, 2015
 *      Author: tadeze
 */

#ifndef ISOLATIONFOREST_HPP_
#define ISOLATIONFOREST_HPP_
#include "Forest.hpp"
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
    template<class Archive>
    void serialize(Archive & archive){
        archive(cereal::make_nvp("ntree",ntree),cereal::make_nvp("nsample",nsample),
                cereal::make_nvp("rsample",rsample),cereal::make_nvp("stopheight",stopheight),
                cereal::make_nvp("trees",trees));

    }
};



#endif /* ISOLATIONFOREST_HPP_ */
