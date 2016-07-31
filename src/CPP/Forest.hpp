/*
 * Forest.h
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#ifndef FOREST_H_
#define FOREST_H_
//#include "utility.hpp"
#include "Tree.hpp"
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
void assTree(Tree *tree,json jnode)
{

    tree->splittingPoint = jnode["splittingatt"];
    tree->splittingPoint = jnode["splittingPoint"];
    tree->depth = jnode["depth"];
    tree->nodeSize =  jnode["nodesize"];
    tree->minAttVal = jnode["minAttVal"];
    tree->maxAttVal = jnode["maxAttVal"];
    
}

void assignTree(Tree* tr,json* rtree)
{

   // std::ofstream logg("verror.log");
 
  // json* rtree = &jff["trees"][2];

    
  //json jtree = jff["trees"][2];
   //logg << jtree["splittingAtt"];
   /*
   logg <<(*rtree)[2];
   logg<<(*rtree)[2]["depth"]<<std::endl;
  logg<<(*rtree)[2]["splittingPoint"]<<std::endl;
 logg<<(*rtree)[2]["splittingAtt"]<<std::endl;
 logg<<(*rtree)[2]["nodesize"]<<std::endl;
 logg<<(*rtree)[2]["minAttVal"]<<std::endl;
   logg <<(*rtree).size();
   */
  
   tr->depth = (*rtree)["depth"];
   tr->splittingAtt = (*rtree)["splittingAtt"];
   tr->splittingPoint= (*rtree)["splittingPoint"];
   tr->nodeSize = (*rtree)["nodesize"];
   tr->minAttVal  = (*rtree)["minAttVal"];
   tr->maxAttVal = (*rtree)["maxAttVal"];
}


// Deserialize using 
void deseralize_bfs(std::string modelname)
{
  //	std::ofstream logg("error.log");
    std::ifstream in(modelname);
    //Forest *iff = new Forest();
  // Will handl file read in the facadlayer 

    json jff;
    
   in>>jff;
   this->nsample = jff["nsample"];
   this->rsample = jff["rsample"];
   this->maxheight = jff["maxheight"];
   this->stopheight = jff["stopheight"];
   this->rangecheck = jff["rangecheck"];
   this->ntree = jff["ntree"];
   
   for(int i=0;i<this->ntree;i++)
   {
    // json* rootTree = &jff["trees"][i];
     Tree* root;
     std::queue<Tree*> qTree;
     int iNode =0;
     int numNodes = (jff["trees"][i]).size();    //rootTree.size();
     while(iNode<numNodes)
     {
         if(iNode==0)  //root node 
         {
            root = new Tree();
            assignTree(root, &jff["trees"][i][iNode]); //;ootTree[i]);
            qTree.push(root);
            iNode++;
         }
         else
         { 
            Tree* node = qTree.front();
            qTree.pop();
            json* jleft = &jff["trees"][i][iNode];//ootTree[iNode];  
            json* jright=NULL;

            //jright =
            if(iNode<(numNodes-1)) jright =&jff["trees"][i][iNode+1];
             // rootTree[iNode+1];
  
            node->leftChild = new Tree();
            assignTree(node->leftChild,jleft);
            qTree.push(node->leftChild);
            if(jright!=NULL)
            {
                node->rightChild = new Tree();
                assignTree(node->rightChild,jright);
                qTree.push(node->rightChild);
            }
            iNode +=2;
         }
     }

    this->trees.push_back(root);

   }
/* 
   
  Tree* tr = new Tree();
  //json* rtree = &jff["trees"][2];
    assignTree(tr,&jff["trees"][2][1]);//  rtree[2]);
  */   
}




json to_json() {
json j;
j["ntree"] = ntree;
j["rsample"] = rsample;
j["maxheight"] = maxheight;
j["stopheight"] = stopheight;
j["rangecheck"]= rangecheck;
j["nsample"] = nsample;
for(int i=0 ;i<ntree;i++){

//j["trees"][i]=serialize_tree(trees[i]);

j["trees"][i]=trees[i]->to_json();    //serialize_bfs(trees[i]);

}

return j;
}

// Serialize

//Serialize using BFS approach 

json serialize_bfs(Tree* tree)
{
	json jroot;

	// Define empty queute
	std::queue<Tree*> qtree ;
	qtree.push(tree);
    int i=0;
	while(!qtree.empty())
    { 
        json j;
        Tree* nextTree = qtree.front();
        qtree.pop();
        if(nextTree==NULL){
            j = NULL;
        }
        else
        {
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








//Deserialize

Forest *deseralize(std::string modelname){
	std::ofstream logg("error.log");
    std::ifstream in(modelname);
     Forest *iff = new Forest();
  
    if(in==nullptr)
        return iff;
    json jff;
    in>>jff;
   iff->nsample = jff["nsample"];
   iff->rsample = jff["rsample"];
   iff->maxheight = jff["maxheight"];
   iff->stopheight = jff["stopheight"];
   iff->rangecheck = jff["rangecheck"];
   iff->ntree = jff["ntree"];
   
   //logg <<iff->rSample;
   logg <<iff->maxheight;
   logg <<iff->stopheight;
   logg<<iff->rangecheck ; 
   logg<<iff->ntree;
   

  logg.close();
  return iff;
}

};
#endif /* FOREST_H_ */
