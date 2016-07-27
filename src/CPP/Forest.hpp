/*
 * Forest.h
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#ifndef FOREST_H_
#define FOREST_H_
#include "utility.hpp"
#include "Tree.hpp"
#include "json/json.hpp"
using json = nlohmann::json;
//#include "cincl.hpp"


class Forest {
public:
	std::vector<Tree*> trees;
	int ntree;
	bool rsample;
	int nsample;
    bool stopheight;
    int maxheight;
   	bool rangecheck;
	//dataset* dataset;  // holds the original dataset
    util::dataset* dataframe;
    Forest()
	{
		rsample = false;
		ntree = 0;
		nsample = 256;
		dataframe = NULL;

	};
Forest(int _ntree,util::dataset* _dataset,int _nsample,int _maxheight, bool _stopheight,bool _rsample)//bool _rangecheck)
    {
	ntree=_ntree;
    dataframe=_dataset;
	nsample=_nsample;
	stopheight=_stopheight;
	maxheight=_maxheight;
 	rsample = _rsample;
//	rangecheck=_rangecheck;
//	Tree::rangeCheck = rangecheck;
    };
virtual ~Forest()
	{
		for (std::vector<Tree*>::iterator it = trees.begin(); it != trees.end();
				++it)
		{
			delete (*it);

		}
    }

	double instanceScore(std::vector<double> &inst);
	std::vector<double> AnomalyScore(util::dataset* df);
	virtual std::vector<double> pathLength(std::vector<double> &inst);
	std::vector<std::vector<double> > pathLength(util::dataset* data);
	std::vector<double> meandepth();
	std::vector<double> ADtest(const std::vector<std::vector<double> > &pathlength, bool weighttotail);
	std::vector<double> importance(std::vector<double> &inst);
	//virtual double getdepth(double *inst,Tree* tree);
	virtual double getdepth(std::vector<double> inst, Tree *tree);
	void getSample(std::vector<int> &sampleIndex,const int nsample,bool rSample,int nrow);
	struct larger
	{
		bool operator()(const std::pair<int,double> p1,const std::pair<int,double> p2)

		{
			return p1.second <p2.second;
		}
	};
    /* virtual function for adaptive forest*/
     virtual int adaptiveForest(double alpha,int stopLimit);

     /*Fixed tree forest */
     virtual void fixedTreeForest() {};

     virtual int confTree(double alpha,double rho,int init_tree);
	 /*
	  * @input two vector v1 and
	 * @return proporation of intersection ,[0,1]
	 */


	double topcommonK(std::vector<int> &v1,std::vector<int> &v2)
	{
		std::vector<int> v3;
		std::sort(v1.begin(),v1.end());
		std::sort(v2.begin(),v2.end());
		std::set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
		return (double)v3.size()/(double)v1.size();
	}

// Serialize

json serialize_tree(Tree* tree){
json j;
if(tree->leftChild!=NULL)
{

j["splittingatt"] = tree->splittingAtt;
j["splittingPoint"] = tree->splittingPoint;
j["depth"]= tree->depth;
j["nodesize"]= tree->nodeSize;
j["minAttVal"] = tree->minAttVal;
j["maxAttVal"] = tree->maxAttVal;
j["lchild"] = serialize_tree(tree->leftChild);
j["rchild"] = serialize_tree(tree->rightChild);

}
/*
else{
    j["lchild"] = nullptr;
    j[1] = nullptr;
}*/
return j;

}

json to_json() {
json j;
j["ntree"] = ntree;
j["rsample"] = rsample;
j["maxheight"] = maxheight;
j["stopheight"] = stopheight;
j["rangecheck"]= rangecheck;
for(int i=0 ;i<ntree;i++){
j["trees"][i]=serialize_tree(trees[i]);
}



return j;
}
//Deserialize

*Forest deseralize(std::string modelname){
    std::ifstream in(modelname);
    if(in==NULL)
        return NULL;
    json jff;
    in >>jff;
    Forest *iff;
   iff->nsample = jff["nsample"];
   iff->rsample = jff["rsample"];
   iff->maxheight = jff["maxheight"];
   iff->stopheight = jff["stopheight"];
   iff->rangecheck = jff["rangecheck"];

}

};
#endif /* FOREST_H_ */
