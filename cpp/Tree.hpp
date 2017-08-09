/*
 * Tree.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */

#ifndef TREE_H_
#define TREE_H_

#include <memory>
#include "utility.hpp"
//#include "cincl.hpp"
//using json= nlohmann::json;

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
class Tree : public std::enable_shared_from_this<Tree> {
   /*
    Tree *leftChild;
	Tree *rightChild;
	Tree *parent;
	*/

private:
    std::shared_ptr<Tree> leftChild,rightChild,parent;
    int nodeSize,splittingAtt,depth;
	double splittingPoint,minAttVal,maxAttVal;
    std::shared_ptr<util::dataset> makeDataset(std::vector<std::vector<double> > &data);


public:
    const std::shared_ptr<Tree> &getLeftChild() const;
    const std::shared_ptr<Tree> &getRightChild() const;
    std::shared_ptr<Tree> getptr(){
        return shared_from_this();
    }
    int getNodeSize() const;

    void setNodeSize(int nodeSize);

    int getSplittingAtt() const;

    void setSplittingAtt(int splittingAtt);

    int getDepth() const;

    void setDepth(int depth);

    double getSplittingPoint() const;

    void setSplittingPoint(double splittingPoint);

    double getMinAttVal() const;

    void setMinAttVal(double minAttVal);

    double getMaxAttVal() const;

    void setMaxAttVal(double maxAttVal);

    static bool rangeCheck;
//    json tracePath(std::vector<double> &inst);
    Tree(): leftChild(nullptr),rightChild(nullptr),parent(nullptr),
            splittingAtt(-1), splittingPoint(-9999),depth(0),nodeSize(0),minAttVal(0),maxAttVal(0){};

	virtual ~Tree() {};
	void iTree(std::vector<int> const &dIndex, const std::shared_ptr<util::dataset> dt, int height, int maxHeight, bool stopheight);
	void iTree(std::vector<int> const &dIndex, std::vector<std::vector<double> > traindata, int height, int maxHeight, bool stopheight);
	
    double pathLength(std::vector<double> &inst);
	double pathLengthM(std::vector<double> &inst);
	int maxTreeDepth();

    //Contribution
   contrib featureContribution(std::vector<double> &inst);
    std::map<int,double> explanation(std::vector<double> &inst){
        return featureContribution(inst).featureContribution();
    };


};

#endif /* TREE_H_ */
