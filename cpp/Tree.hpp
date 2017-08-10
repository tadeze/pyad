/*
 * Tree.h
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */

#ifndef TREE_H_
#define TREE_H_

#include "cereal/cereal.hpp"
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include <memory>
#include "utility.hpp"
#include "featureContribution.hpp"
//#include "cincl.hpp"
//using json= nlohmann::json;

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
   contrib featureContribution(std::vector<double> &inst) const;
    std::map<int,double> explanation(std::vector<double> &inst) const;
    // Serialization
    template<class Archive>
            void  serialize(Archive & archive){
        archive(cereal::make_nvp("nodesize",nodeSize),cereal::make_nvp("depth",depth),
                cereal::make_nvp("splittingAtt",splittingAtt),cereal::make_nvp("splittingPoint",splittingPoint),
                cereal::make_nvp("minAttVal",minAttVal),cereal::make_nvp("maxAttVal",maxAttVal),
                cereal::make_nvp("leftChild",leftChild),cereal::make_nvp("rightChild",rightChild)

        );
    }


};

#endif /* TREE_H_ */
