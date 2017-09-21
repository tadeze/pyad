/*
 * Forest.cpp
 *
 *  Created on: Aug 12, 2015
 *      Author: tadeze
 */

#include "Forest.hpp"

double Forest::getdepth(std::vector<double> &inst, const std::shared_ptr<Tree> &tree) {
    return tree->pathLength(inst,this->cmv);
}


/*
 * Accepts single point (row) and return Anomaly Score
 */
double Forest::instanceScore(std::vector<double> &inst) {

    double avgPathLength = util::mean(pathLength(inst));
    double scores = pow(2, -avgPathLength / util::avgPL(this->nsample));
    return scores;

}

/*
 * Score for  a set of dataframe in dataset
 */
std::vector<double> Forest::AnomalyScore(std::shared_ptr<util::dataset> df) {
    std::vector<double> scores;
    //iterate through all points
    for (int inst = 0; inst < df->nrow; inst++) {
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

std::vector<double> Forest::pathLength(std::vector<double> &inst) {
    std::vector<double> depth;
    /*for (std::vector<std::shared_ptr<Tree>>::iterator it = this->trees.begin(); it != trees.end();
         ++it) {*/
    for(auto const &tree : this->trees)
        depth.push_back(getdepth(inst,tree)); //#tree->pathLength(inst,cmv));

    /*depth.push_back((*it)->pathLength(inst));

    }*/
    return depth;
}


/* PathLength for all points
*/
std::vector<std::vector<double> > Forest::pathLength(std::shared_ptr<util::dataset> data) {
    std::vector<std::vector<double> > depths;
    for (int r = 0; r < data->nrow; r++)
        depths.push_back(pathLength(data->data[r]));
    return depths;
}

/* Compute the feature importance of a point
 * input: *inst data instance
 * output: feature importance
 * status: Incomplete!!
 */
std::map<int, double> Forest::importance(std::vector<double> &inst) {
    //Need to be re-implemented
    std::map<int, double> totalexplan;
    auto featureExplanation = Forest::featureContrib(inst);
    for (const auto feature : featureExplanation) {
        for (auto explan : feature) {
            if (totalexplan.count(explan.first) > 0)
                totalexplan[explan.first] += explan.second;
            else
                totalexplan.insert(explan);
        }
    }

    return totalexplan;
}

//Sample data from the datset
void Forest::getSample(std::vector<int> &sampleIndex, const int nsample, bool rsample, int nrow) {
    sampleIndex.clear();
    if (rsample && nsample < nrow)
        util::sampleI(0, nrow - 1, nsample, sampleIndex); //sample nsample
    else
        util::sampleI(0, nrow - 1, nrow, sampleIndex); //shuffle all index of the data

}


/*
 * Feature contribution
 */
    std::vector<std::map<int, double> > Forest::featureContrib(std::vector<double> &inst) {
        // Iterate through all trees and collect their contributions

        std::vector<std::map<int, double> > contributions;
        for (auto &tree : this->trees) {
            auto treeexplanation = tree->featureContribution(inst).featureContribution();
            contributions.push_back(treeexplanation);
        }

        return contributions;
    }

void Forest::tracePath(std::vector<double> &inst, std::ostream &out){

    auto featureCont = Forest::featureContrib(inst);
    for (const auto tree : this->trees) {
        auto treePath = tree->featureContribution(inst).contributions;
        for(auto feat : treePath) {
            out <<tree->getParent_id()<<","<<feat.first << "," << inst[feat.first]<<",[";
            for(auto depth_path: feat.second)
                out<<depth_path<<",";
            out<<"]";
            out<<"\n";
        }
    }

}

