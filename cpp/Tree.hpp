/*
 * Tree.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */

#ifndef TREE_H_
#define TREE_H_
#include "utility.hpp"
//#include "cincl.hpp"
using json= nlohmann::json;

/* Defines feature contribution of a given point 
 */
struct Contrib{
    int feature;
    std::map<int,std::vector<double> > contributions;
    void addcont(int index, double depth){
        if(contributions.count(index)<1) {
            std::vector<double> contr;
            contr.push_back(depth);
            contributions.insert({index,contr});
        }
        else{
            contributions[index].push_back(depth);
        }
    }
    std::map<int,double> featureContribution(){
        std::map<int,double> explanation;
        for(const auto & contr : contributions){
            double expl=0.0;
            expl = 1.0/contr.second[0]; //This consider the top most cut.     
            //for(auto depth : contr.second) // if we consider all cuts 
            //   expl += 1.0/depth;
            explanation.insert({contr.first,expl});

        }
        return explanation;
    }

};
typedef  struct Contrib contrib;
class Tree {
protected:
    std::shared_ptr<Tree> leftChild,rightChild,parent;
    /*Tree *leftChild;
	Tree *rightChild;
	Tree *parent;*/
	int nodeSize;
	int splittingAtt;
	double splittingPoint;
	int depth;
	double minAttVal,maxAttVal;
	osu::data::dataset *makeDataset(std::vector<std::vector<double> > &data);

public:
    /** Later the property will be private this will be their access point */
    int getNodeSize(){ return this->nodeSize;}
    int getSplittingAtt() { return this->splittingAtt;}
    double getSplittingPoint() { return this->splittingPoint;}
    int getDepth() { return this->depth;}
    double getMinAttVal() {return this->minAttVal;}
    double getMaxAttVal() { return this->maxAttVal;}
    std::shared_ptr<Tree> lChild() {return leftChild;}
    std::shared_ptr<Tree> rChild() { return rightChild;}
    /*
    Tree* lChild() { return leftChild;}
    Tree* rChild() {return rightChild;}
   */
    static bool rangeCheck;
    json tracePath(std::vector<double> &inst); 
    Tree(): leftChild(nullptr),rightChild(nullptr),parent(nullptr),
            splittingAtt(-1), splittingPoint(-9999),depth(0),nodeSize(0),minAttVal(0),maxAttVal(0){};

	virtual ~Tree() {};
    /*    delete leftChild; //check if deleting the child is need.
        delete rightChild;

	};
*/
	void iTree(std::vector<int> const &dIndex, const osu::data::dataset *dt, int height, int maxHeight, bool stopheight);
	void iTree(std::vector<int> const &dIndex, std::vector<std::vector<double> > traindata, int height, int maxHeight, bool stopheight);
	
    double pathLength(std::vector<double> &inst);
	double pathLengthM(std::vector<double> &inst);
	int maxTreeDepth();
    void assignTree(std::shared_ptr<Tree> tr, std::shared_ptr<json> rtree);

    //Contribution
   contrib featureContribution(std::vector<double> &inst);
    std::map<int,double> explanation(std::vector<double> &inst){
        return featureContribution(inst).featureContribution();
    };

    json to_json();
    void from_json(json &jsontree);


};

#endif /* TREE_H_ */
