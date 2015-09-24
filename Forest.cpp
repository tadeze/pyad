/*
 * Forest.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#include "Forest.hpp"

double Forest::getdepth(double* inst,Tree* tree)
{
	return tree->pathLength(inst);
}

/*
 * Accepts single point (row) and return Anomaly Score
 */
double Forest::instanceScore(double *inst)
{

	double avgPathLength = util::mean(pathLength(inst));
	double scores = pow(2, -avgPathLength / util::avgPL(this->nsample));
	return scores;

}

/*
 * Score for  a set of dataframe in dataset
 */
std::vector<double> Forest::AnomalyScore(doubleframe* df)
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
 * Return instance depth in all trees
*/

std::vector<double> Forest::pathLength(double *inst)
{
	std::vector<double> depth;
	for (std::vector<Tree*>::iterator it = this->trees.begin(); it != trees.end();
			++it)
	{

 		 depth.push_back((*it)->pathLength(inst));


	}
      // pnt++;   //for logging purpose
	return depth;
}


/* PathLength for all points
*/
std::vector<std::vector<double> > Forest::pathLength(doubleframe*  data)
{
	std::vector < std::vector<double> > depths;
	for (int r = 0; r < data->nrow; r++)
		depths.push_back(pathLength(data->data[r]));
	return depths;
}
/*
 * Anderson_Darling test from the pathlength
 */
/*
vector<double> IsolationForest::ADtest(const vector<vector<double> > &pathlength,bool weighttotail)
{

//Will fix later
	return ADdistance(pathlength,weighttotail);
}*/
/* Compute the feature importance of a point
 * input: *inst data instance
 * output: feature importance
 * status: Incomplete!!
 */
std::vector<double> Forest::importance(double *inst)
{
	//Need to be re-implemented
	//Incorrect code
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

void Forest::addAdaptiveTree(Tree* tree,double alpha)
{
//	this->nsample = nsample;
	double tk = ceil(alpha*4*dataset->nrow);
	vector<int> sampleIndex;
//	this->rSample = rSample;

	vector<double> totalDepth(dataset->nrow,0);
    int conv_cnt =0;  //convergence counter

	vector<double> squaredDepth(dataset->nrow,0);
 	priority_queue<pair<int,double>,vector<pair<int,double> >, larger> pq;
	double  ntree=0.0;
	bool converged=false;

	vector<pair<int ,int> > topk;
 util::logfile<<"ntree,index,currentscore,probinter \n";
	vector<int> topIndex(tk);
	vector<int> prevIndex;
	double prob =0;
	while (!converged) {
     pq= priority_queue<pair<int,double>,vector<pair<int,double> >,larger >();


		//Sample data for training
		getSample(sampleIndex,nsample,rsample,dataset->nrow);
		//build a tree based on the sample and add to forest
		Tree *tree = new Tree();
		tree->iTree(sampleIndex,dataset, 0, maxheight, stopheight);
		this->trees.push_back(tree);
		ntree++;
		double d,scores,dbar;
		topIndex.clear();
		for (int inst = 0; inst <dataset->nrow; inst++)
		{
			d = getdepth(dataset->data[inst],tree);
			totalDepth[inst] += d;
			squaredDepth[inst] +=d*d;
			dbar=totalDepth[inst]/ntree;
			scores = pow(2, -dbar / util::avgPL(this->nsample));
			pq.push( pair<int, double>(inst,scores));


		}
		//if we have 1 tree we don't have variance
		if(ntree<2)
		{
			for(int i=0;i<tk;i++)
			 {
				inserTopK(topk,pq.top().first);
				topIndex.push_back(pq.top().first);
			 	 pq.pop();

			 }
		prevIndex = topIndex;
			continue;

		}


         *	double maxCIWidth =0;


		for(int i=0;i<tk;i++)  //where tk is top 2*\alpha * N index element
		{ 	//int index=0;

	              int index= pq.top().first;
		      //inserTopK(topk,pq.top().first);
		//	topIndex.push_back(pq.top().first);
		//	int index =topk.at(i).first;
			double mn = totalDepth[index]/ntree;
			double var = squaredDepth[index]/ntree -(mn*mn);
			double halfwidth = 1.96*sqrt(var)/sqrt(ntree);
			double scoreWidth = pow(2, -(mn-halfwidth) / avgPL(this->nsample)) -pow(2, -(mn+halfwidth)/ avgPL(this->nsample));
			maxCIWidth=max(maxCIWidth,scoreWidth);
	    //		logfile<<ntree<<","<<pq.top().first<<","<<pq.top().second<<","<<prob<<"\n";
	    //	logfile<<i<<ntree<<","<<index<<","<<pq.top().second<<","<<","<<var<<","<<scoreWidth<<"\n";
				pq.pop();
		}




		for(int i=0;i<tk;i++){
            //where tk is top 2*\alpha * N index element

            //int index=0;
            //pq.top().first;
		    //	inserTopK(topk,pq.top().first);
			topIndex.push_back(pq.top().first);
		    //	int index =topk.at(i).first;
		    //	double mn = totalDepth[index]/ntree;
		    //	double var = squaredDepth[index]/ntree -(mn*mn);
		    //	double halfwidth = 1.96*sqrt(var)/sqrt(ntree);
		    //	double scoreWidth = pow(2, -(mn-halfwidth) / avgPL(this->nsample)) -pow(2, -(mn+halfwidth)/ avgPL(this->nsample));
		    //	maxCIWidth=max(maxCIWidth,scoreWidth);
			util::logfile<<ntree<<","<<pq.top().first<<","<<pq.top().second<<","<<prob<<"\n";
			//logfile<<ntree<<","<<topk.at(i).first<<","<<pq.top().second<<","<<pow(2,-mn/avgPL(this->nsample))<<","<<var<<","<<scoreWidth<<"\n";
			pq.pop();
		}

	prob=topcommonK(topIndex,prevIndex);
	prevIndex = topIndex;
    if(prob==1)
        conv_cnt++;
    else
        conv_cnt=0;
    converged = conv_cnt>5;
	//	sort(topk.begin(),topk.end(),larger());
	// logfile <<"Tree number "<<ntree<<" built with confidence\t"<<maxCIWidth<<endl;

    //	 logfile <<"Tree number "<<ntree<<" built with confidence\t"<<maxCIWidth<<endl;
    //   		converged = prob>0.99 && ntree >100;     //maxCIWidth <=tau;
	}

    //return this;
}


*/

