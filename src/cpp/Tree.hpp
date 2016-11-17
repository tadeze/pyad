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
class Tree
{
;

public:
    Tree *leftChild;
	Tree *rightChild;
	Tree *parent;
	int nodeSize;
	int splittingAtt;
	double splittingPoint;
	int depth;
	double minAttVal,maxAttVal;

	util::dataset *makeDataset(std::vector<std::vector<double> > &data);
    json to_json();
    void from_json();
    /** Later the property will be private this will be their access point */
    int getNodeSize(){ return this->nodeSize;}
    int getSplittingAtt() { return this->splittingAtt;}
    double getSplittingPoint() { return this->splittingPoint;}
    int getDepth() { return this->depth;}
    double getMinAttVal() {return this->minAttVal;}
    double getMaxAttVal() { return this->maxAttVal;}
    Tree* lChild() { return this->leftChild;}
    Tree* rChild() {return this->rightChild;}
    static bool rangeCheck;
    json tracePath(std::vector<double> &inst); 
    Tree()
	{
		leftChild = NULL;
		rightChild = NULL;
		parent = NULL;
		splittingAtt = -1;
		splittingPoint = -9999;
		depth = 0;
		nodeSize = 0;
		minAttVal=maxAttVal=0;
	}
	;

	virtual ~Tree()
	{
        delete leftChild; //check if deleting the child is need.
        delete rightChild;

	};
    
	void iTree(std::vector<int> const &dIndex, const util::dataset *dt, int height, int maxHeight, bool stopheight);
	void iTree(std::vector<int> const &dIndex, std::vector<std::vector<double> > traindata, int height, int maxHeight, bool stopheight);
	
    double pathLength(std::vector<double> &inst);
	double pathLengthM(std::vector<double> &inst);
	int maxTreeDepth(); 

};

#endif /* TREE_H_ */
