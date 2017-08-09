/*
 * Forest.h
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#ifndef FOREST_H_
#define FOREST_H_
//#include "utility.hpp"
#include <memory>
#include "Tree.hpp"
//using json = nlohmann::json;
//#include "cincl.hpp"
class Forest {

public:
    
	//std::vector<Tree*> trees;
	std::vector<std::shared_ptr<Tree> > trees;
    int ntree;
	bool rsample;
	int nsample;
    bool stopheight;
    int maxheight;
   	bool rangecheck;
	std::shared_ptr<util::dataset> dataframe;
    //std::unique_ptr<util::dataset> dataframe;
    Forest() {
		rsample = false;
		ntree = 0;
		nsample = 256;
		dataframe = NULL;
	};
Forest(int _ntree,std::shared_ptr<util::dataset> _dataset,int _nsample,
       int _maxheight, bool _stopheight,bool _rsample){
	ntree=_ntree;
    dataframe=_dataset;
	nsample=_nsample;
	stopheight=_stopheight;
	maxheight=_maxheight;
 	rsample = _rsample;
   };
virtual ~Forest(){};
	/*{
		for (std::vector<Tree*>::iterator it = trees.begin(); it != trees.end();
				++it) {
			delete (*it);
		}
    }*/
	double instanceScore(std::vector<double> &inst);
	std::vector<double> AnomalyScore(std::shared_ptr<util::dataset> df);
	virtual std::vector<double> pathLength(std::vector<double> &inst);
	std::vector<std::vector<double> > pathLength(std::shared_ptr<util::dataset> data);
	std::vector<double> meandepth();
	std::vector<double> ADtest(const std::vector<std::vector<double> > &pathlength, bool weighttotail);
	std::map<int, double> importance(std::vector<double> &inst);
	virtual double getdepth(std::vector<double> inst, std::shared_ptr<Tree> tree);
	void getSample(std::vector<int> &sampleIndex,const int nsample,bool rSample,int nrow);
	struct larger {
		bool operator()(const std::pair<int,double> p1,const std::pair<int,double> p2)

		{
			return p1.second <p2.second;
		}
	};
    /* virtual function for adaptive forest*/
     virtual int adaptiveForest(double alpha,int stopLimit){return 0;};

     /*Fixed tree forest */
     virtual void fixedTreeForest() {};

     virtual int confTree(double alpha,double rho,int init_tree){return 0;};
	 /*
	  * @input two vector v1 and
	 * @return proporation of intersection ,[0,1]
	 */

	double topcommonK(std::vector<int> &v1,std::vector<int> &v2) {
		std::vector<int> v3;
		std::sort(v1.begin(),v1.end());
		std::sort(v2.begin(),v2.end());
		std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
		return (double)v3.size()/(double)v1.size();
	}
//json to_json();
//void from_json(std::ifstream &input);

virtual std::vector<std::map<int,double> > featureContrib(std::vector<double> &inst);
};
#endif /* FOREST_H_ */
