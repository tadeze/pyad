/*
 * IsolationForest.cpp
 *
 *  Created on: Mar, 2015
 *      Author: Tadeze
 */

#include "IsolationForest.hpp"
IsolationForest::IsolationForest(int _ntree,doubleframe* _df,
		int _nsample,int _maxheight, bool _stopheight,bool _rsample)
:Forest(_ntree,_df,_nsample,_maxheight,_stopheight,_rsample)
{



}
//Build forest using defined number of trees

void IsolationForest::buildForest()
{
	std::vector<int> sampleIndex;

		//build forest through all trees
		for (int n = 0; n < this->ntree; n++)
		{

			//Sample and shuffle the data.
			sampleIndex.clear();
			getSample(sampleIndex,nsample,rsample,dataset->nrow);

			//build tree
			Tree *tree = new Tree();
			tree->iTree(sampleIndex,dataset, 0, maxheight, stopheight);
			this->trees.push_back(tree); //add tree to forest
		//	Tree::treeIndx++;
		 }


}

int IsolationForest::adaptiveForest(double alpha){
    //Build the RForest model
	double tk = ceil(alpha*2*dataset->nrow);
    std::vector<int> sampleIndex(this->nsample);
    //logfile<<"point,tree,x1,x2\n";
    bool converged = false;
    int convCounter =0 ;
    double ntree=0;
    std::vector<int> topKIndex;
    std::vector<int> prevTopKIndex;
    std::vector<double> totalDepth(dataset->nrow,0);
    double prob=0.0;
    std::priority_queue<std::pair<int,double>,std::vector<std::pair<int,double> >, larger> pq;
    while(!converged)
    {
    	pq= std::priority_queue<std::pair<int,double>,std::vector<std::pair<int,double> >,larger >();

            //get sample data
            getSample(sampleIndex,nsample,rsample,dataset->nrow);

            //Fill the sampleIndex with indices of the sample rotated data
            Tree *tree  = new Tree();
            tree->iTree(sampleIndex,dataset,0,maxheight,stopheight);
            this->trees.push_back(tree);
            ntree++;
            double d,dbar;
            topKIndex.clear();
            for (int inst = 0; inst <dataset->nrow; inst++)
            {
            d = this->getdepth(dataset->data[inst],tree);
            totalDepth[inst] += d;
            dbar=totalDepth[inst]/ntree;
            pq.push(std::pair<int, double>(inst,dbar));
           	}

        for(int i=0;i<tk;i++)
         {
        	  	topKIndex.push_back(pq.top().first);
            	pq.pop();

        }
        if(ntree==1)
        {
        	prevTopKIndex = topKIndex;
        	continue;
        }

        prob=topcommonK(topKIndex,prevTopKIndex);
        prevTopKIndex = topKIndex;
        if(prob==1)
             convCounter++;
          else
            convCounter=0;
         converged = convCounter>5;



      if(ntree<50)
    	  converged=false;

    }





return ntree;
}

