/*
 * Forest.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#include "Forest.hpp"

double Forest::getdepth(std::vector<double> inst,Tree* tree)
{
	return tree->pathLength(inst);
}


/*
 * Accepts single point (row) and return Anomaly Score
 */
double Forest::instanceScore(std::vector<double> &inst)
{

	double avgPathLength = util::mean(pathLength(inst));
	double scores = pow(2, -avgPathLength / util::avgPL(this->nsample));
	return scores;

}

/*
 * Score for  a set of dataframe in dataset
 */
std::vector<double> Forest::AnomalyScore(util::dataset* df)
{
	std::vector<double> scores;
	//iterate through all points
	for (int inst = 0; inst <df->nrow; inst++)
	{
		scores.push_back(instanceScore(df->data[inst]));
	}
	return scores;
}

/*
 * Trace path of a piont in a tree.
 */





/*
 * Return instance depth in all trees
*/

std::vector<double> Forest::pathLength(std::vector<double> &inst)
{
	std::vector<double> depth;
	for (std::vector<Tree*>::iterator it = this->trees.begin(); it != trees.end();
			++it)
	{

 		 depth.push_back((*it)->pathLength(inst));


	}
	return depth;
}



/* PathLength for all points
*/
std::vector<std::vector<double> > Forest::pathLength(util::dataset*  data)
{
	std::vector < std::vector<double> > depths;
	for (int r = 0; r < data->nrow; r++)
		depths.push_back(pathLength(data->data[r]));
	return depths;
}

/* Compute the feature importance of a point
 * input: *inst data instance
 * output: feature importance
 * status: Incomplete!!
 */
std::vector<double> Forest::importance(std::vector<double> &inst)
{
	//Need to be re-implemented
	std::vector<double> depth;
	for (std::vector<Tree*>::iterator it = this->trees.begin(); it != trees.end();
			++it)
	{

		depth.push_back(ceil((*it)->pathLength(inst)));

	}
return depth;
}

//Sample data from the datset
void Forest::getSample(std::vector<int> &sampleIndex,const int nsample,bool rsample,int nrow)
{
	sampleIndex.clear();
	if (rsample && nsample < nrow)
		util::sampleI(0, nrow - 1, nsample, sampleIndex); //sample nsample
	else
		util::sampleI(0, nrow - 1, nrow, sampleIndex); //shuffle all index of the data



}
/*
int Forest::adaptiveForest(double alpha,int stopLimit)
{
//For now remove warning compiler
 return (int)alpha*stopLimit;
}
int Forest::confTree(double alpha,double rho, int init_tree){
	//For now remove warning
	return (int)alpha*rho*init_tree;
}
*/
// Serialization

json Forest::to_json() {
    json j;
    j["ntree"] = ntree;
    j["rsample"] = rsample;
    j["maxheight"] = maxheight;
    j["stopheight"] = stopheight;
    j["rangecheck"]= rangecheck;
    j["nsample"] = nsample;

    for(int i=0 ;i<ntree;i++){
        //j["trees"][i]=serialize_bfs(trees[i]);
    j["trees"][i] = trees[i]->to_json();

    }

    return j;

}

void Forest::from_json(std::ifstream &input) {
    json jff;
    input>>jff;

    this->nsample = jff["nsample"];
    this->rsample = jff["rsample"];
    this->maxheight = jff["maxheight"];
    this->stopheight = jff["stopheight"];
    this->rangecheck = jff["rangecheck"];
    this->ntree = jff["ntree"];

    for(int i=0;i<this->ntree;i++) {
        // json* rootTree = &jff["trees"][i];
        Tree *rootTree = new Tree();
        rootTree->from_json(jff["trees"][i]);
        this->trees.push_back(rootTree);
    }
       /* int iNode =0;
        int numNodes = (jff["trees"][i]).size();





        std::queue<Tree*> qTree;
        int iNode =0;
        int numNodes = (jff["trees"][i]).size();    //rootTree.size();
        while(iNode<numNodes)
        {
            if(iNode==0)  //root node
            {
                root = new Tree();
                assignTree(root, &jff["trees"][i][iNode]);
                qTree.push(root);
                iNode++;
            }
            else
            {
                Tree* node = qTree.front();
                qTree.pop();
                json* jleft = &jff["trees"][i][iNode];//ootTree[iNode];
                json* jright=NULL;

                if(iNode<(numNodes-1)) jright =&jff["trees"][i][iNode+1];

                if(jleft!=NULL && (*jleft)["depth"]>0)
                {
                    node->leftChild = new Tree();
                    assignTree(node->leftChild,jleft);
                    qTree.push(node->leftChild);
                }
                else
                {

                }

                if(jright!=NULL && (*jright)["depth"]>0)
                {
                    node->rightChild = new Tree();
                    assignTree(node->rightChild,jright);
                    qTree.push(node->rightChild);
                }
                iNode +=2;
            }
        }

        this->trees.push_back(root);
    }*/

}