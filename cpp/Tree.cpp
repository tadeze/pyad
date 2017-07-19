/*
 * Tree.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: Tadeze
 */
#include "Tree.hpp"
#include<stack>
bool Tree::rangeCheck=true;
double const MISSING_VALUE = -9999.0;
int const NULL_TREE_CHILD_DEPTH = -999;

util::dataset *Tree::makeDataset(std::vector<std::vector<double> > &data) {
	util::dataset *dt = new util::dataset();
	dt->data = data;
	dt->ncol = (int) data[0].size();
	dt->nrow = (int) data.size();
	return dt;
}


void Tree::iTree(std::vector<int> const &dIndex,
        std::vector<std::vector<double> > traindata, int height, int maxheight, bool stopheight)
{
   util::dataset *dt =makeDataset(traindata);
   this->iTree(dIndex,dt,height,maxheight,stopheight);
   delete dt;
}


void Tree::iTree(std::vector<int> const &dIndex,const util::dataset *dt, int height, int maxheight, bool stopheight)
{
	this->depth = height; //Tree height
	// Set size of the node
	nodeSize = dIndex.size();
	//stop growing if condition
	if (dIndex.size() <= 1 || (stopheight && this->depth > maxheight))
	{
		return;
	}
	//*** Need modification
	//Initialize minmax array for holding max and min of an attributes

	std::vector<std::vector<double> > minmax;
	std::vector<double> tmp;

	for (int j = 0; j < dt->ncol; j++)
	{
	//initialize max and min to random value
		tmp.push_back(dt->data[dIndex[0]][j]);
		tmp.push_back(dt->data[dIndex[0]][j]);
		minmax.push_back(tmp);
		tmp.clear();
	}

    //Compute max and min of each attribute
	for (unsigned i = 0; i <dIndex.size() ; i++)
	{
		//vector<double> inst = data->data[i];
		for (int j = 0; j < dt->ncol; j++)
		{
			if (dt->data[dIndex.at(i)][j] < minmax[j].at(0))
				minmax[j].at(0) =dt->data[dIndex.at(i)][j];
			if (dt->data[dIndex.at(i)][j] > minmax.at(j).at(1))
				minmax[j].at(1) = dt->data[dIndex.at(i)][j];
		}

	}

	//use only valid attributes
   	 std::vector<int> attributes;
	for (int j = 0; j < dt->ncol; j++)
	{
		if (minmax[j][0] < minmax[j][1])
		{
			attributes.push_back(j);
		}
	}
	//return if no valid attribute found
	if (attributes.size() == 0)
		return;
	//Randomly pick an attribute and a split point

	this->splittingAtt = attributes[util::randomI(0,attributes.size()-1)]; //randx];
	this->splittingPoint =util::randomD(minmax[this->splittingAtt][0],minmax[this->splittingAtt][1]);
	this->minAttVal =minmax[this->splittingAtt][0];
	this->maxAttVal = minmax[this->splittingAtt][1];
	std::vector <int> lnodeData;
	std::vector <int> rnodeData;
	//Split the node into two
	for (unsigned i = 0; i < dIndex.size(); i++)
	{
		if ( dt->data[dIndex.at(i)][splittingAtt] >= splittingPoint &&
				(dt->data[dIndex.at(i)][splittingAtt]!=minmax[this->splittingAtt][0]))

		{
			rnodeData.push_back(dIndex.at(i));
		}
		else
		{
			lnodeData.push_back(dIndex.at(i));
		}
	}
	leftChild = new Tree(); //&dataL,height+1,maxheight);
	leftChild->parent = this;
	leftChild->iTree(lnodeData,dt, this->depth + 1, maxheight, stopheight);

	rightChild = new Tree(); //&dataR,height+1,maxheight);
	rightChild->parent = this;
	rightChild->iTree(rnodeData,dt, this->depth + 1, maxheight, stopheight);

}



//Need to be fixed later.
json Tree::tracePath(std::vector<double> &inst)
{
	json jroot,j;
	// Define empty queute
	std::queue<Tree*> qtree ;
	qtree.push(this);

	double instAttVal = inst[this->splittingAtt];
	double depth=0.0;

while(!qtree.empty())
    {

        Tree* nextTree = qtree.front();
        qtree.pop();
        if(nextTree==NULL){
            j = NULL;
           break;
        }
        else
        {
		if(Tree::rangeCheck==true)
 		{

			if((instAttVal < this->minAttVal && util::randomD(instAttVal,this->minAttVal)<this->minAttVal) ||
			(instAttVal >this->minAttVal && util::randomD(instAttVal,this->maxAttVal)>this->maxAttVal))
				{
				depth+=1.0;
				 continue;
				}
		}


 		instAttVal = inst[nextTree->splittingAtt];


		if ( instAttVal >= nextTree->splittingPoint)
		   qtree.push(nextTree->rightChild);
	//	temp= temp->rightChild;
		else
		  	 qtree.push(nextTree->leftChild);

	//temp = temp->leftChild;


            j["depth"] = nextTree->depth;
            j["splittingAtt"] = nextTree->splittingAtt;
            j["splittingPoint"] = nextTree->splittingPoint;
            j["depth"]= nextTree->depth;
            j["nodesize"]=nextTree->nodeSize;
            j["minAttVal"] = nextTree->minAttVal;
            j["maxAttVal"] = nextTree->maxAttVal;


	//if(nextTree->leftChild!=NULL){ //Assuming balanced tree
           // qtree.push(nextTree->leftChild);
           // qtree.push(nextTree->rightChild);
          }
     jroot.push_back(j);
        }

return jroot;

}






/*
 * takes instance as vector of double
 *//*
 * takes instance as vector of double
 */
double Tree::pathLengthM(std::vector<double> &inst){


	double instAttVal = inst[this->splittingAtt];
	double depth=0.0;
	Tree *temp =this;
	while(temp!=NULL){

		if(Tree::rangeCheck==true)
 		{

			if(instAttVal < this->minAttVal && util::randomD(instAttVal,this->minAttVal)<this->minAttVal)
				return depth+1.0;
			if(instAttVal >this->minAttVal && util::randomD(instAttVal,this->maxAttVal)>this->maxAttVal)
				return depth+1.0;
		}
 		instAttVal = inst[temp->splittingAtt];
		if ( instAttVal >= temp->splittingPoint)
			temp= temp->rightChild;
		else
			temp = temp->leftChild;

		depth +=1.0;
	}

	return depth+util::avgPL(temp->nodeSize);
}

/*
 * takes instance as vector of double
 */
double Tree::pathLength(std::vector<double> &inst){


 	if (this->leftChild==NULL||this->rightChild==NULL) { ///referenced as null for some input data .
               	return util::avgPL(this->nodeSize);
        }
	//Range check added
    double instAttVal = inst[this->splittingAtt];
	if(Tree::rangeCheck==true) {

		if(instAttVal < this->minAttVal && util::randomD(instAttVal,this->minAttVal)<this->minAttVal)
			return 1.0;
		if(instAttVal >this->minAttVal && util::randomD(instAttVal,this->maxAttVal)>this->maxAttVal)
			return 1.0;

	}
	//Checking missing data for the attribute.

	if(instAttVal==MISSING_VALUE) {

	double leftNodeSize = (double)this->leftChild->nodeSize/(double)this->nodeSize;

	return 	 (1.0-leftNodeSize)*(this->rightChild->pathLength(inst) + 1.0)+
leftNodeSize*(this->leftChild->pathLength(inst) + 1.0);

 	}


 	//Logging the isolation process
 	//	logfile<<tmpVar<<","<<this->splittingAtt<<","<<this->splittingPoint<<"\n";

	if (instAttVal >= this->splittingPoint) {


		return this->rightChild->pathLength(inst) + 1.0;

	}
	else {
		return this->leftChild->pathLength(inst) + 1.0;
	}



}



//std::vector<std::vector<double>>
//std::map<int,double>
struct Contrib Tree::featureContribution(std::vector<double> &inst){

    Tree *root = this;
    double instAttVal;
    double depth =0.0;
    Contrib contribution;
    while((root->rightChild != NULL) || (root->leftChild!=NULL)) {
        instAttVal = inst[root->splittingAtt];

        //contributions[root->splittingAtt] = depth + util::avgPL(root->nodeSize);

        if (instAttVal >= root->splittingPoint)
             root = root->rightChild;
        else
            root = root->leftChild ;
        depth = depth +1.0;
        if (root->splittingAtt!=-1)
        contribution.addcont(root->splittingAtt,depth+util::avgPL(root->nodeSize));

    }
    depth = util::avgPL(root->nodeSize) + depth;
    return contribution;//.featureContribution();

}
int Tree::maxTreeDepth(){
	if (!this) return 0;
	std::stack<Tree*> s;
	s.push(this);
	int maxDepth=0;
	Tree *prev =NULL;
	 while (!s.empty()) {
	    Tree *curr = s.top();
	    if (!prev || prev->leftChild == curr || prev->rightChild== curr) {
	    if(curr->leftChild)
	    	s.push(curr->leftChild);
	     else if (curr->rightChild)
	        s.push(curr->rightChild);
	    }
	    else if (curr->leftChild == prev) {
	      if (curr->rightChild)
	        s.push(curr->rightChild);
	    }
	    else {
	      s.pop();
	    }

	    prev = curr;
	    if ((int)s.size() > maxDepth)
	      maxDepth = s.size();
	  }
	  return maxDepth;

}
json Tree::to_json(){

	json jroot;

	// Define empty queute
	std::queue<Tree*> qtree ;
	qtree.push(this);
	int i=0;
	while(!qtree.empty()) {
		json j;
		Tree* nextTree = qtree.front();
		qtree.pop();
		if(nextTree==NULL){
			j["depth"] =  NULL_TREE_CHILD_DEPTH;
		}
		else {
			j["depth"] = nextTree->depth;
			j["splittingAtt"] = nextTree->splittingAtt;
			j["splittingPoint"] = nextTree->splittingPoint;
			j["depth"]= nextTree->depth;
			j["nodesize"]=nextTree->nodeSize;
			j["minAttVal"] = nextTree->minAttVal;
			j["maxAttVal"] = nextTree->maxAttVal;
			qtree.push(nextTree->leftChild);
			qtree.push(nextTree->rightChild);
		}

		jroot.push_back(j);
		i++;
	}

	return jroot;

}
void Tree::assignTree(Tree* tr,json* rtree){

    tr->depth = (*rtree)["depth"];
    tr->splittingAtt = (*rtree)["splittingAtt"];
    tr->splittingPoint= (*rtree)["splittingPoint"];
    tr->nodeSize = (*rtree)["nodesize"];
    tr->minAttVal  = (*rtree)["minAttVal"];
    tr->maxAttVal = (*rtree)["maxAttVal"];
}
void Tree::from_json(json &jsontree){
    Tree* root;
    std::queue<Tree*> qTree;
    unsigned iNode =0;
    auto numNodes = jsontree.size();    //rootTree.size();
    while(iNode<numNodes){
        if(iNode==0){  //root node
            root = this;//new Tree();
            assignTree(root, &jsontree[iNode]);
            qTree.push(root);
            iNode++;
        }
        else {
            Tree* node = qTree.front();
            qTree.pop();
            json* jleft = &jsontree[iNode];//ootTree[iNode];
            json* jright=NULL;

            if(iNode<(numNodes-1))
                jright =&jsontree[iNode+1];

            if(jleft!=NULL && (*jleft)["depth"]>0) {
                node->leftChild = new Tree();
                assignTree(node->leftChild,jleft);
                qTree.push(node->leftChild);
            }
            if(jright!=NULL && (*jright)["depth"]>0){
                node->rightChild = new Tree();
                assignTree(node->rightChild,jright);
                qTree.push(node->rightChild);
            }
            iNode +=2;
        }
    }

}

